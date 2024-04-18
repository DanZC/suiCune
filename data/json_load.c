#include "../util/json.h"
#include "../constants.h"
#include "constant_strings.h"
#include <assert.h>
#include "json_load.h"
#include "../engine/items/mart.h"

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

void JSONLoadTables(void) {
    JSONLoadMarts();
}
