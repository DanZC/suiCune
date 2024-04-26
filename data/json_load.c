#include "../util/json.h"
#include "../constants.h"
#include "constant_strings.h"
#include <assert.h>
#include "json_load.h"
#include "../engine/items/mart.h"
#include "wild/johto_grass.h"
#include "pokemon/base_stats.h"

const char MartJSONPath[] = "data/items/marts.json";

u32_flag_s JSONStringToConstant(json_value_t* const value) {
    json_string_t* str = json_value_as_string(value);
    if(str == NULL) {
        fprintf(stderr, "Could not parse JSON value as string.");
        return u32_flag((uint32_t)-1, false);
    }
    u32_flag_s res = FindConstantValueByString(str->string);
    if(!res.flag) {
        fprintf(stderr, "Could not find constant value '%s'.", str->string);
        return u32_flag((uint32_t)-1, false);
    }
    return res;
}

int_flag_s JSONValueToInt(json_value_t* const value) {
    json_number_t* num = json_value_as_number(value);
    if(num == NULL) {
        fprintf(stderr, "Could not parse JSON value as number.");
        return int_flag(-1, false);
    }
    return int_flag(atoi(num->number), true);
}

int JSONValueToIntUnsafe(json_value_t* const value) {
    json_number_t* num = json_value_as_number(value);
    assert(num);
    return atoi(num->number);
}

void JSONLoadMarts(void) {
    JSONDestroyMarts();
    asset_s a = LoadTextAsset(MartJSONPath);
    json_value_t* root = json_parse(a.ptr, a.size);
    assert(root);

    json_object_t* root_object = json_value_as_object(root);
    assert(root_object);

    for(json_object_element_t* it = root_object->start; it != NULL; it = it->next) {
        json_array_t* arr = json_value_as_array(it->value);
        item_t* mart = malloc(sizeof(item_t) * arr->length);
        uint8_t i = 0;
        for(json_array_element_t* arr_it = arr->start; arr_it != NULL; arr_it = arr_it->next) {
            u32_flag_s res2 = JSONStringToConstant(arr_it->value);
            if(!res2.flag) {
                mart[i++] = NO_ITEM;
            }
            else {
                mart[i++] = res2.a;
            }
        }
        u32_flag_s res = FindConstantValueByString(it->name->string);
        if(!res.flag) {
            free(mart);
            continue;
        }
        MartsSizes[res.a] = arr->length;
        Marts[res.a] = mart;
    }
    free(root);
    FreeAsset(a);
}

void JSONDestroyMarts(void){
    for(int i = 0; i < NUM_MARTS; ++i) {
        if(Marts[i]) {
            free(Marts[i]);
            Marts[i] = NULL;
        }
    }
}

static void JSONLoadWildGrassEncounterTable(struct WildGrassMons** table, const char* json_path) {
    if(*table) free(*table);
    asset_s a = LoadTextAsset(json_path);
    json_value_t* root = json_parse(a.ptr, a.size);
    assert(root);

    json_object_t* root_object = json_value_as_object(root);
    assert(root_object);

    *table = malloc(sizeof(struct WildGrassMons) * (root_object->length + 1));
    json_object_element_t* map_el = root_object->start;
    for(size_t i = 0; i < root_object->length; ++i) {
        u32_flag_s map_id = FindConstantValueByString(map_el->name->string);
        if(!map_id.flag)
            break;
        (*table)[i].mapGroup = (uint8_t)(map_id.a >> 8);
        (*table)[i].mapNumber = (uint8_t)(map_id.a & 0xff);
        json_object_t* obj = json_value_as_object(map_el->value);
        for(json_object_element_t* obj_it = obj->start; obj_it; obj_it = obj_it->next) {
            if(strcmp(obj_it->name->string, "encounter_rates") == 0) {
                json_array_t* encounter_rates_arr = json_value_as_array(obj_it->value);
                assert(encounter_rates_arr->length >= 3);
                (*table)[i].encounterRates[0] = JSONValueToIntUnsafe(encounter_rates_arr->start->value) percent;
                (*table)[i].encounterRates[1] = JSONValueToIntUnsafe(encounter_rates_arr->start->next->value) percent;
                (*table)[i].encounterRates[2] = JSONValueToIntUnsafe(encounter_rates_arr->start->next->next->value) percent;
            }
            else if(strcmp(obj_it->name->string, "encounters") == 0) {
                json_object_t* encounters = json_value_as_object(obj_it->value);
                for(json_object_element_t* encounters_it = encounters->start; encounters_it; encounters_it = encounters_it->next) {
                    uint8_t j = 0;
                    if(strcmp(encounters_it->name->string, "morn") == 0) 
                        j = MORN_F;
                    else if(strcmp(encounters_it->name->string, "day") == 0)
                        j = DAY_F;
                    else if(strcmp(encounters_it->name->string, "nite") == 0)
                        j = NITE_F;
                    json_array_t* encounters_arr = json_value_as_array(encounters_it->value);
                    assert(encounters_arr->length == lengthof((*table)[i].mons[0]));
                    json_array_element_t* encounters_arr_it = encounters_arr->start;
                    uint8_t k = 0;
                    while(encounters_arr_it) {
                        json_object_t* encounter_obj = json_value_as_object(encounters_arr_it->value);
                        for(json_object_element_t* encounter_obj_it = encounter_obj->start; encounter_obj_it; encounter_obj_it = encounter_obj_it->next) {
                            if(strcmp(encounter_obj_it->name->string, "level") == 0) {
                                (*table)[i].mons[j][k].level = JSONValueToIntUnsafe(encounter_obj_it->value);
                            }
                            else if(strcmp(encounter_obj_it->name->string, "species") == 0) {
                                u32_flag_s species_res = JSONStringToConstant(encounter_obj_it->value);
                                (*table)[i].mons[j][k].species = (species_t)species_res.a;
                            }
                        }
                        k++;
                        encounters_arr_it = encounters_arr_it->next;
                    }
                }
            }
        }
        map_el = map_el->next;
    }
    (*table)[root_object->length].mapGroup = (uint8_t)-1;
    (*table)[root_object->length].mapNumber = (uint8_t)-1;
    FreeAsset(a);
    free(root);
}

const char WildJSONPath[] = "data/wild/johto_grass.json";

void JSONLoadWildEncounters(void) {
    JSONLoadWildGrassEncounterTable(&JohtoGrassWildMons, WildJSONPath);
}

const char PokemonBaseStatsPath[] = "data/pokemon/base_stats.json";
void JSONLoadPokemonBaseStats(struct BaseData* data) {
    asset_s a = LoadTextAsset(PokemonBaseStatsPath);
    json_value_t* root = json_parse(a.ptr, a.size);
    assert(root);

    json_array_t* root_array = json_value_as_array(root);
    uint32_t i = 0;
    json_array_element_t* array_it = root_array->start;
    while(array_it && i < NUM_POKEMON) {
        memset(data + i, 0, sizeof(data[i]));
        json_object_t* mon_obj = json_value_as_object(array_it->value);
        for(json_object_element_t* mon_field_it = mon_obj->start; mon_field_it; mon_field_it = mon_field_it->next) {
            const char* fkey = mon_field_it->name->string;
            if(strcmp(fkey, "dexNo") == 0) {
                u32_flag_s res = JSONStringToConstant(mon_field_it->value);
                if(res.flag)
                    data[i].dexNo = (dex_t)res.a;
            }
            else if(strcmp(fkey, "gender") == 0) {
                u32_flag_s res = JSONStringToConstant(mon_field_it->value);
                if(res.flag)
                    data[i].gender = (uint8_t)res.a;
                else
                    data[i].gender = GENDER_F50;
            }
            else if(strcmp(fkey, "catchRate") == 0) {
                int_flag_s res = JSONValueToInt(mon_field_it->value);
                if(res.flag)
                    data[i].catchRate = (uint8_t)res.a;
            }
            else if(strcmp(fkey, "exp") == 0) {
                int_flag_s res = JSONValueToInt(mon_field_it->value);
                if(res.flag)
                    data[i].exp = (uint8_t)res.a;
            }
            else if(strcmp(fkey, "eggSteps") == 0) {
                int_flag_s res = JSONValueToInt(mon_field_it->value);
                if(res.flag)
                    data[i].eggSteps = (uint8_t)res.a;
            }
            else if(strcmp(fkey, "unknown1") == 0) {
                int_flag_s res = JSONValueToInt(mon_field_it->value);
                if(res.flag)
                    data[i].unknown1 = (uint8_t)res.a;
            }
            else if(strcmp(fkey, "unknown2") == 0) {
                int_flag_s res = JSONValueToInt(mon_field_it->value);
                if(res.flag)
                    data[i].unknown2 = (uint8_t)res.a;
            }
            else if(strcmp(fkey, "growthRate") == 0) {
                u32_flag_s res = JSONStringToConstant(mon_field_it->value);
                if(res.flag)
                    data[i].growthRate = (uint8_t)res.a;
                else
                    data[i].growthRate = GROWTH_SLOW;
            }
            else if(strcmp(fkey, "types") == 0) {
                json_array_t* types_arr = json_value_as_array(mon_field_it->value);
                if(types_arr->length == 1) {
                    u32_flag_s res = JSONStringToConstant(types_arr->start->value);
                    if(res.flag) {
                        data[i].types[0] = (uint8_t)res.a;
                        data[i].types[1] = (uint8_t)res.a;
                    }
                }
                else {
                    uint32_t j = 0;
                    for(json_array_element_t* types_it = types_arr->start; types_it && j < 2; j++, types_it = types_it->next) {
                        u32_flag_s res = JSONStringToConstant(types_it->value);
                        if(res.flag)
                            data[i].types[j] = res.a;
                    }
                }
            }
            else if(strcmp(fkey, "eggGroups") == 0) {
                json_array_t* egg_groups_arr = json_value_as_array(mon_field_it->value);
                if(egg_groups_arr->length == 1) {
                    u32_flag_s res = JSONStringToConstant(egg_groups_arr->start->value);
                    if(res.flag) {
                        data[i].eggGroups = (uint8_t)((res.a << 4) | res.a);
                    }
                }
                else {
                    json_array_element_t* egg_groups_it = egg_groups_arr->start;

                    uint8_t temp[2] = {EGG_NONE, EGG_NONE};
                    uint32_t j = 0;
                    while(egg_groups_it && j < 2) {
                        u32_flag_s res = JSONStringToConstant(egg_groups_it->value);
                        if(res.flag)
                            temp[j] = (uint8_t)res.a;
                        j++;
                        egg_groups_it = egg_groups_it->next;
                    }
                    data[i].eggGroups = (temp[0] << 4) | temp[1];
                }
            }
            else if(strcmp(fkey, "TMHM") == 0) {
                char buffer[32];
                json_array_t* tmhm_arr = json_value_as_array(mon_field_it->value);
                for(json_array_element_t* tmhm_it = tmhm_arr->start; tmhm_it; tmhm_it = tmhm_it->next) {
                    json_string_t* tm_name = json_value_as_string(tmhm_it->value);
                    sprintf(buffer, "%s_TMNUM", tm_name->string);
                    u32_flag_s res = FindConstantValueByString(buffer);
                    if(res.flag) {
                        data[i].TMHM[res.a >> 3] |= (1 << (res.a & 7));
                    }
                }
            }
            else if(strcmp(fkey, "stats") == 0) {
                json_array_t* stats_arr = json_value_as_array(mon_field_it->value);
                json_array_element_t* stats_it = stats_arr->start;
                uint32_t j = 0;
                while(stats_it && j < 6) {
                    int_flag_s res = JSONValueToInt(stats_it->value);
                    if(res.flag)
                        data[i].stats[j] = (uint8_t)res.a;
                    j++;
                    stats_it = stats_it->next;
                }
            }
        }
        i++;
        array_it = array_it->next;
    }
    FreeAsset(a);
    free(root);
}

void JSONLoadTables(void) {
    JSONLoadMarts();
    JSONLoadWildEncounters();
    JSONLoadPokemonBaseStats(BasePokemonData);
}
