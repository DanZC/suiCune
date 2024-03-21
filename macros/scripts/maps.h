
#define MAP_ID(_a) GROUP_##_a, MAP_##_a
#define MAP_ID_(_a) (struct MapId){.mapGroup=GROUP_##_a, .mapNumber=MAP_##_a}
