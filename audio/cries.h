#pragma once

// audio/cries.asm
enum {
    oCry_Marill                       = 0x0000,
    oCry_Togepi                       = 0x0009,
    oCry_Togetic                      = 0x000f,
    oCry_Spinarak                     = 0x0015,
    oCry_Raikou                       = 0x001e,
    oCry_Hoothoot                     = 0x0027,
    oCry_Sentret                      = 0x0030,
    oCry_Slowking                     = 0x0036,
    oCry_Mareep                       = 0x003f,
    oCry_Cyndaquil                    = 0x0045,
    oCry_Chikorita                    = 0x004e,
    oCry_Gligar                       = 0x0057,
    oCry_Girafarig                    = 0x005d,
    oCry_Slugma                       = 0x0066,
    oCry_Ledyba                       = 0x006c,
    oCry_Wooper                       = 0x0075,
    oCry_Donphan                      = 0x007e,
    oCry_Typhlosion                   = 0x0087,
    oCry_Natu                         = 0x0090,
    oCry_Teddiursa                    = 0x0099,
    oCry_Sunflora                     = 0x00a2,
    oCry_Ampharos                     = 0x00ab,
    oCry_Totodile                     = 0x00b4,
    oCry_Cleffa                       = 0x00bd,
    oCry_Pichu                        = 0x00c6,
    oCry_Aipom                        = 0x00cf,
    oCry_Dunsparce                    = 0x00d8,
    oCry_Magcargo                     = 0x00e1,
    oCry_Entei                        = 0x00ea,
    oCry_Mantine                      = 0x00f3,
    oCry_Entei_Ch5                    = 0x00fc,
    oCry_Entei_Ch6                    = 0x0113,
    oCry_Entei_Ch8                    = 0x0126,
    oCry_Magcargo_Ch5                 = 0x0133,
    oCry_Magcargo_Ch6                 = 0x0152,
    oCry_Magcargo_Ch8                 = 0x0171,
    oCry_Dunsparce_Ch5                = 0x0182,
    oCry_Dunsparce_Ch6                = 0x01a5,
    oCry_Dunsparce_Ch8                = 0x01b0,
    oCry_Slowking_Ch5                 = 0x01ba,
    oCry_Slowking_Ch6                 = 0x01d9,
    oCry_Slowking_Ch8                 = 0x01f0,
    oCry_Pichu_Ch5                    = 0x0209,
    oCry_Pichu_Ch6                    = 0x022a,
    oCry_Pichu_Ch8                    = 0x0241,
    oCry_Marill_Ch5                   = 0x0251,
    oCry_Marill_Ch6                   = 0x0270,
    oCry_Marill_Ch8                   = 0x028b,
    oCry_Togepi_Ch5                   = 0x029e,
    oCry_Togepi_Ch6                   = 0x02a1,
    oCry_Togetic_Ch5                  = 0x02b4,
    oCry_Togetic_Ch6                  = 0x02b7,
    oCry_Spinarak_Ch5                 = 0x02c7,
    oCry_Spinarak_Ch6                 = 0x02da,
    oCry_Spinarak_Ch8                 = 0x02ed,
    oCry_Raikou_Ch5                   = 0x02fa,
    oCry_Raikou_Ch6                   = 0x0319,
    oCry_Raikou_Ch8                   = 0x033c,
    oCry_Hoothoot_Ch5                 = 0x0355,
    oCry_Hoothoot_Ch6                 = 0x0378,
    oCry_Hoothoot_Ch8                 = 0x0393,
    oCry_Sentret_Ch5                  = 0x03a0,
    oCry_Sentret_Ch6                  = 0x03a8,
    oCry_Sentret_Ch8                  = 0x03b3,
    oCry_Mareep_Ch5                   = 0x03ba,
    oCry_Mareep_Ch6                   = 0x03c2,
    oCry_Cyndaquil_Ch5                = 0x03d5,
    oCry_Cyndaquil_Ch6                = 0x03d8,
    oCry_Gligar_Ch8                   = 0x03f7,
    oCry_Cyndaquil_Ch8                = 0x03f7,
    oCry_Chikorita_Ch5                = 0x03fe,
    oCry_Chikorita_Ch6                = 0x0401,
    oCry_Chikorita_Ch8                = 0x0418,
    oCry_Gligar_Ch5                   = 0x041f,
    oCry_Girafarig_Ch5                = 0x0424,
    oCry_Girafarig_Ch6                = 0x042c,
    oCry_Girafarig_Ch8                = 0x0443,
    oCry_Slugma_Ch5                   = 0x0453,
    oCry_Slugma_Ch8                   = 0x046a,
    oCry_Ledyba_Ch5                   = 0x0477,
    oCry_Ledyba_Ch6                   = 0x047f,
    oCry_Ledyba_Ch8                   = 0x049a,
    oCry_Wooper_Ch5                   = 0x04ad,
    oCry_Donphan_Ch5                  = 0x04ad,
    oCry_Wooper_Ch6                   = 0x04c8,
    oCry_Donphan_Ch6                  = 0x04c8,
    oCry_Wooper_Ch8                   = 0x04e3,
    oCry_Donphan_Ch8                  = 0x04f3,
    oCry_Teddiursa_Ch5                = 0x0503,
    oCry_Typhlosion_Ch5               = 0x0503,
    oCry_Teddiursa_Ch6                = 0x053a,
    oCry_Typhlosion_Ch6               = 0x053a,
    oCry_Typhlosion_Ch8               = 0x0559,
    oCry_Natu_Ch5                     = 0x0566,
    oCry_Natu_Ch6                     = 0x0581,
    oCry_Sunflora_Ch6                 = 0x0581,
    oCry_Natu_Ch8                     = 0x059c,
    oCry_Sunflora_Ch8                 = 0x059c,
    oCry_Teddiursa_Ch8                = 0x05af,
    oCry_Sunflora_Ch5                 = 0x05b6,
    oCry_Mantine_Ch5                  = 0x05bb,
    oCry_Mantine_Ch6                  = 0x05c4,
    oCry_Mantine_Ch8                  = 0x05cb,
    oCry_Ampharos_Ch5                 = 0x05d2,
    oCry_Ampharos_Ch6                 = 0x05ef,
    oCry_Ampharos_Ch8                 = 0x0606,
    oCry_Totodile_Ch5                 = 0x0619,
    oCry_Totodile_Ch6                 = 0x0630,
    oCry_Totodile_Ch8                 = 0x0647,
    oCry_Cleffa_Ch5                   = 0x0654,
    oCry_Cleffa_Ch6                   = 0x067b,
    oCry_Cleffa_Ch8                   = 0x068e,
    oCry_Aipom_Ch5                    = 0x06a1,
    oCry_Aipom_Ch6                    = 0x06c0,
    oCry_Aipom_Ch8                    = 0x06df,
    oCry_Nidoran_M                    = 0x06fc,
    oCry_Nidoran_F                    = 0x0705,
    oCry_Slowpoke                     = 0x070e,
    oCry_Kangaskhan                   = 0x0717,
    oCry_Charmander                   = 0x0720,
    oCry_Grimer                       = 0x0729,
    oCry_Voltorb                      = 0x0732,
    oCry_Muk                          = 0x073b,
    oCry_Oddish                       = 0x0744,
    oCry_Raichu                       = 0x074d,
    oCry_Nidoqueen                    = 0x0756,
    oCry_Diglett                      = 0x075f,
    oCry_Seel                         = 0x0768,
    oCry_Drowzee                      = 0x0771,
    oCry_Pidgey                       = 0x077a,
    oCry_Bulbasaur                    = 0x0783,
    oCry_Spearow                      = 0x078c,
    oCry_Rhydon                       = 0x0795,
    oCry_Golem                        = 0x079e,
    oCry_Blastoise                    = 0x07a7,
    oCry_Pidgeotto                    = 0x07b0,
    oCry_Weedle                       = 0x07b9,
    oCry_Caterpie                     = 0x07c2,
    oCry_Ekans                        = 0x07cb,
    oCry_Fearow                       = 0x07d4,
    oCry_Clefairy                     = 0x07dd,
    oCry_Venonat                      = 0x07e6,
    oCry_Lapras                       = 0x07ef,
    oCry_Metapod                      = 0x07f8,
    oCry_Squirtle                     = 0x0801,
    oCry_Paras                        = 0x080a,
    oCry_Growlithe                    = 0x0813,
    oCry_Krabby                       = 0x081c,
    oCry_Psyduck                      = 0x0825,
    oCry_Rattata                      = 0x082e,
    oCry_Vileplume                    = 0x0837,
    oCry_Vulpix                       = 0x0840,
    oCry_Weepinbell                   = 0x0849,
    oCry_Unused_Ch5                   = 0x0852,
    oCry_Unused_Ch6                   = 0x086d,
    oCry_Unused_Ch8                   = 0x0888,
    oCry_Raichu_Ch5                   = 0x089e,
    oCry_Raichu_Ch6                   = 0x08bb,
    oCry_Raichu_Ch8                   = 0x08dc,
    oCry_Vileplume_Ch5                = 0x08f5,
    oCry_Vileplume_Ch6                = 0x090c,
    oCry_Vileplume_Ch8                = 0x091f,
    oCry_Vulpix_Ch5                   = 0x092c,
    oCry_Vulpix_Ch6                   = 0x094f,
    oCry_Vulpix_Ch8                   = 0x0972,
    oCry_Rhydon_Ch5                   = 0x0982,
    oCry_Rhydon_Ch6                   = 0x09a1,
    oCry_Rhydon_Ch8                   = 0x09c4,
    oCry_Weepinbell_Ch5               = 0x09da,
    oCry_Weepinbell_Ch6               = 0x09f1,
    oCry_Weepinbell_Ch8               = 0x0a08,
    oCry_Kangaskhan_Ch5               = 0x0a15,
    oCry_Kangaskhan_Ch6               = 0x0a34,
    oCry_Kangaskhan_Ch8               = 0x0a53,
    oCry_Bulbasaur_Ch5                = 0x0a60,
    oCry_Bulbasaur_Ch6                = 0x0a7b,
    oCry_Bulbasaur_Ch8                = 0x0a96,
    oCry_Spearow_Ch5                  = 0x0aa6,
    oCry_Spearow_Ch6                  = 0x0ac9,
    oCry_Spearow_Ch8                  = 0x0aec,
    oCry_Nidoran_M_Ch5                = 0x0af6,
    oCry_Nidoran_M_Ch6                = 0x0b05,
    oCry_Nidoran_M_Ch8                = 0x0b14,
    oCry_Pidgey_Ch5                   = 0x0b1e,
    oCry_Pidgey_Ch6                   = 0x0b31,
    oCry_Pidgey_Ch8                   = 0x0b44,
    oCry_Voltorb_Ch5                  = 0x0b4e,
    oCry_Voltorb_Ch6                  = 0x0b68,
    oCry_Voltorb_Ch8                  = 0x0b69,
    oCry_Muk_Ch5                      = 0x0b7c,
    oCry_Muk_Ch6                      = 0x0b8b,
    oCry_Muk_Ch8                      = 0x0b9a,
    oCry_Grimer_Ch5                   = 0x0ba4,
    oCry_Grimer_Ch6                   = 0x0bb7,
    oCry_Grimer_Ch8                   = 0x0bc9,
    oCry_Diglett_Ch5                  = 0x0bca,
    oCry_Diglett_Ch6                  = 0x0bf5,
    oCry_Diglett_Ch8                  = 0x0c14,
    oCry_Seel_Ch5                     = 0x0c2d,
    oCry_Seel_Ch6                     = 0x0c54,
    oCry_Seel_Ch8                     = 0x0c7a,
    oCry_Slowpoke_Ch5                 = 0x0c7b,
    oCry_Slowpoke_Ch6                 = 0x0c8a,
    oCry_Slowpoke_Ch8                 = 0x0c98,
    oCry_Drowzee_Ch5                  = 0x0c99,
    oCry_Drowzee_Ch6                  = 0x0cb8,
    oCry_Drowzee_Ch8                  = 0x0ce7,
    oCry_Nidoran_F_Ch5                = 0x0d06,
    oCry_Nidoran_F_Ch6                = 0x0d19,
    oCry_Nidoran_F_Ch8                = 0x0d2c,
    oCry_Nidoqueen_Ch5                = 0x0d39,
    oCry_Nidoqueen_Ch6                = 0x0d58,
    oCry_Nidoqueen_Ch8                = 0x0d7b,
    oCry_Oddish_Ch5                   = 0x0d94,
    oCry_Oddish_Ch6                   = 0x0da7,
    oCry_Oddish_Ch8                   = 0x0dba,
    oCry_Charmander_Ch5               = 0x0dc4,
    oCry_Charmander_Ch6               = 0x0de3,
    oCry_Charmander_Ch8               = 0x0e02,
    oCry_Clefairy_Ch5                 = 0x0e15,
    oCry_Clefairy_Ch6                 = 0x0e24,
    oCry_Clefairy_Ch8                 = 0x0e36,
    oCry_Caterpie_Ch5                 = 0x0e37,
    oCry_Caterpie_Ch6                 = 0x0e46,
    oCry_Caterpie_Ch8                 = 0x0e55,
    oCry_Lapras_Ch5                   = 0x0e5f,
    oCry_Lapras_Ch6                   = 0x0e76,
    oCry_Lapras_Ch8                   = 0x0e8d,
    oCry_Golem_Ch5                    = 0x0e9a,
    oCry_Golem_Ch6                    = 0x0ead,
    oCry_Golem_Ch8                    = 0x0ec0,
    oCry_Blastoise_Ch5                = 0x0ecd,
    oCry_Blastoise_Ch6                = 0x0ee8,
    oCry_Blastoise_Ch8                = 0x0f03,
    oCry_Pidgeotto_Ch5                = 0x0f16,
    oCry_Pidgeotto_Ch6                = 0x0f25,
    oCry_Pidgeotto_Ch8                = 0x0f34,
    oCry_Paras_Ch5                    = 0x0f3e,
    oCry_Paras_Ch6                    = 0x0f61,
    oCry_Paras_Ch8                    = 0x0f88,
    oCry_Weedle_Ch5                   = 0x0fa4,
    oCry_Weedle_Ch6                   = 0x0fbf,
    oCry_Weedle_Ch8                   = 0x0fda,
    oCry_Ekans_Ch5                    = 0x0fed,
    oCry_Ekans_Ch6                    = 0x1000,
    oCry_Ekans_Ch8                    = 0x1013,
    oCry_Metapod_Ch5                  = 0x1020,
    oCry_Metapod_Ch6                  = 0x1043,
    oCry_Metapod_Ch8                  = 0x105e,
    oCry_Venonat_Ch5                  = 0x106e,
    oCry_Venonat_Ch6                  = 0x1089,
    oCry_Venonat_Ch8                  = 0x10a4,
    oCry_Squirtle_Ch5                 = 0x10b7,
    oCry_Squirtle_Ch6                 = 0x10d2,
    oCry_Squirtle_Ch8                 = 0x10ed,
    oCry_Fearow_Ch5                   = 0x10fd,
    oCry_Fearow_Ch6                   = 0x1120,
    oCry_Fearow_Ch8                   = 0x1143,
    oCry_Growlithe_Ch5                = 0x1156,
    oCry_Growlithe_Ch6                = 0x1169,
    oCry_Growlithe_Ch8                = 0x117c,
    oCry_Krabby_Ch5                   = 0x1189,
    oCry_Krabby_Ch6                   = 0x119c,
    oCry_Krabby_Ch8                   = 0x11af,
    oCry_Psyduck_Ch5                  = 0x11bc,
    oCry_Psyduck_Ch6                  = 0x11df,
    oCry_Psyduck_Ch8                  = 0x1201,
    oCry_Rattata_Ch5                  = 0x1202,
    oCry_Rattata_Ch6                  = 0x1215,
    oCry_Rattata_Ch8                  = 0x1228,
};