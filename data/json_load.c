#include "../util/json.h"
#include "../constants.h"
#include "constant_strings.h"
#include <assert.h>
#include "json_load.h"
#include "../engine/items/mart.h"
#include "wild/johto_grass.h"

const char MartJSONPath[] = "data/items/marts.json";

void JSONLoadMarts(void) {
    JSONDestroyMarts();
    asset_s a = LoadTextAsset(MartJSONPath);
    json_value_t* root = json_parse(a.ptr, a.size);
    assert(root);

    json_object_t* root_object = json_value_as_object(root);
    assert(root_object);

    json_object_element_t* it = root_object->start;
    while(it != NULL) {
        json_array_t* arr = json_value_as_array(it->value);
        item_t* mart = malloc(sizeof(item_t) * arr->length);
        uint8_t i = 0;
        json_array_element_t* arr_it = arr->start;
        while(arr_it != NULL) {
            u32_flag_s res2 = FindConstantValueByString(json_value_as_string(arr_it->value)->string);
            if(!res2.flag) {
                mart[i++] = NO_ITEM;
            }
            else {
                mart[i++] = res2.a;
            }
            arr_it = arr_it->next;
        }
        const char* s = it->name->string;
        u32_flag_s res = FindConstantValueByString(s);
        if(!res.flag) {
            it = it->next;
            free(mart);
            continue;
        }
        MartsSizes[res.a] = arr->length;
        Marts[res.a] = mart;
        it = it->next;
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
        json_object_element_t* obj_it = obj->start;
        while(obj_it) {
            if(strcmp(obj_it->name->string, "encounter_rates") == 0) {
                json_array_t* encounter_rates_arr = json_value_as_array(obj_it->value);
                assert(encounter_rates_arr->length >= 3);
                (*table)[i].encounterRates[0] = atoi(json_value_as_number(encounter_rates_arr->start->value)->number) percent;
                (*table)[i].encounterRates[1] = atoi(json_value_as_number(encounter_rates_arr->start->next->value)->number) percent;
                (*table)[i].encounterRates[2] = atoi(json_value_as_number(encounter_rates_arr->start->next->next->value)->number) percent;
            }
            else if(strcmp(obj_it->name->string, "encounters") == 0) {
                json_object_t* encounters = json_value_as_object(obj_it->value);
                json_object_element_t* encounters_it = encounters->start;
                while(encounters_it) {
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
                        json_object_element_t* encounter_obj_it = encounter_obj->start;
                        while(encounter_obj_it) {
                            if(strcmp(encounter_obj_it->name->string, "level") == 0) {
                                (*table)[i].mons[j][k].level = atoi(json_value_as_number(encounter_obj_it->value)->number);
                            }
                            else if(strcmp(encounter_obj_it->name->string, "species") == 0) {
                                u32_flag_s species_res = FindConstantValueByString(json_value_as_string(encounter_obj_it->value)->string);
                                (*table)[i].mons[j][k].species = (species_t)species_res.a;
                            }
                            encounter_obj_it = encounter_obj_it->next;
                        }
                        k++;
                        encounters_arr_it = encounters_arr_it->next;
                    }
                    encounters_it = encounters_it->next;
                }
            }
            obj_it = obj_it->next;
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

void JSONLoadTables(void) {
    JSONLoadMarts();
    JSONLoadWildEncounters();
}
