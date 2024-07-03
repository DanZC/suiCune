#include "../constants.h"

const uint8_t CreditsScript[] = {

// Clear the banner.
    CREDITS_CLEAR,

// Pokemon Crystal Version Staff
                   STAFF, 1,

    CREDITS_WAIT, 8,

// Play the credits music.
    CREDITS_MUSIC,

    CREDITS_WAIT2, 10,

    CREDITS_WAIT, 1,

// Update the banner.
    CREDITS_SCENE, 0, // Pichu

                DIRECTOR, 1,
          SATOSHI_TAJIRI, 2,

    CREDITS_WAIT, 12,

              CODIRECTOR, 1,
          JUNICHI_MASUDA, 2,

    CREDITS_WAIT, 12,

             PROGRAMMERS, 0,
          SOUSUKE_TAMADA, 1,
          HISASHI_SOGABE, 2,
            KEITA_KAGAYA, 3,
       YOSHINORI_MATSUDA, 4,

    CREDITS_WAIT, 12,

             PROGRAMMERS, 0,
        SHIGEKI_MORIMOTO, 1,
        TETSUYA_WATANABE, 2,
           TAKENORI_OOTA, 3,

    CREDITS_WAIT, 12,

       GRAPHICS_DIRECTOR, 1,
            KEN_SUGIMORI, 2,

    CREDITS_WAIT, 12,

          MONSTER_DESIGN, 0,
            KEN_SUGIMORI, 1,
       MOTOFUMI_FUJIWARA, 2,
        SHIGEKI_MORIMOTO, 3,
        HIRONOBU_YOSHIDA, 4,
            SATOSHI_OOTA, 5,

    CREDITS_WAIT, 12,

          MONSTER_DESIGN, 0,
          ATSUKO_NISHIDA, 1,
             MUNEO_SAITO, 2,
          RENA_YOSHIKAWA, 3,

    CREDITS_WAIT, 12,

       POKEMON_ANIMATION, 1,
        HIRONOBU_YOSHIDA, 2,
             JUN_OKUTANI, 3,

    CREDITS_WAIT, 12,

// Clear the banner.
    CREDITS_CLEAR,

    CREDITS_WAIT, 1,

// Update the banner.
    CREDITS_SCENE, 1, // Smoochum

         GRAPHICS_DESIGN, 0,
        HIRONOBU_YOSHIDA, 1,
             JUN_OKUTANI, 2,
          ASUKA_IWASHITA, 3,
        TETSUYA_WATANABE, 4,

    CREDITS_WAIT, 12,

            CREDIT_MUSIC, 0,
          JUNICHI_MASUDA, 1,
           MORIKAZU_AOKI, 2,
             GO_ICHINOSE, 3,

    CREDITS_WAIT, 12,

    CREDIT_SOUND_EFFECTS, 0,
           MORIKAZU_AOKI, 1,
          JUNICHI_MASUDA, 2,
        TETSUYA_WATANABE, 3,

    CREDITS_WAIT, 12,

             GAME_DESIGN, 0,
          JUNICHI_MASUDA, 1,
        SHIGEKI_MORIMOTO, 2,
           KOHJI_NISHINO, 3,

    CREDITS_WAIT, 12,

             GAME_DESIGN, 0,
            TETSUJI_OOTA, 1,
             HITOMI_SATO, 2,
        KENJI_MATSUSHIMA, 3,

    CREDITS_WAIT, 12,

           GAME_SCENARIO, 0,
          JUNICHI_MASUDA, 1,
           KOHJI_NISHINO, 2,
     TOSHINOBU_MATSUMIYA, 3,
        KENJI_MATSUSHIMA, 4,

    CREDITS_WAIT, 12,

            POKEDEX_TEXT, 1,
     TOSHINOBU_MATSUMIYA, 2,

    CREDITS_WAIT, 12,

        TOOL_PROGRAMMING, 1,
          SOUSUKE_TAMADA, 2,
           TAKENORI_OOTA, 3,

    CREDITS_WAIT, 12,

       PARAMETRIC_DESIGN, 1,
           KOHJI_NISHINO, 2,

    CREDITS_WAIT, 12,

// Clear the banner.
    CREDITS_CLEAR,

    CREDITS_WAIT, 1,

// Update the banner.
    CREDITS_SCENE, 2, // Ditto

           SCRIPT_DESIGN, 1,
            TETSUJI_OOTA, 2,
           NOBUHIRO_SEYA, 3,

    CREDITS_WAIT, 12,

         MAP_DATA_DESIGN, 1,
            TETSUJI_OOTA, 2,
         KAZUHITO_SEKINE, 3,

    CREDITS_WAIT, 12,

              MAP_DESIGN, 0,
            TETSUJI_OOTA, 1,
           KOHJI_NISHINO, 2,
           NOBUHIRO_SEYA, 3,

    CREDITS_WAIT, 12,

            COORDINATION, 1,
         HIROYUKI_ZINNAI, 2,

    CREDITS_WAIT, 12,

               PRODUCERS, 0,
            SATORU_IWATA, 1,
          SATOSHI_YAMATO, 2,
        SHIGERU_MIYAMOTO, 3,

    CREDITS_WAIT, 12,

               PRODUCERS, 1,
      TSUNEKAZU_ISHIHARA, 2,

    CREDITS_WAIT, 12,

// Clear the banner.
    CREDITS_CLEAR,

    CREDITS_WAIT, 1,

// Update the banner.
    CREDITS_SCENE, 3, // Igglybuff

        US_VERSION_STAFF, 2,

    CREDITS_WAIT, 9,

         US_COORDINATION, 1,
             GAIL_TILDEN, 2,
           HIRO_NAKAMURA, 3,

    CREDITS_WAIT, 12,

         US_COORDINATION, 1,
          JUNICHI_MASUDA, 2,
           SETH_MCMAHILL, 3,

    CREDITS_WAIT, 12,

         US_COORDINATION, 1,
        HIROTO_ALEXANDER, 2,
        TERESA_LILLYGREN, 3,

    CREDITS_WAIT, 12,

        TEXT_TRANSLATION, 1,
           NOB_OGASAWARA, 2,

    CREDITS_WAIT, 12,

             PROGRAMMERS, 1,
         TERUKI_MURAKAWA, 2,
         KAZUYOSHI_OSAWA, 3,

    CREDITS_WAIT, 12,

            PAAD_TESTING, 1,
          THOMAS_HERTZOG, 2,
            ERIK_JOHNSON, 3,

    CREDITS_WAIT, 12,

         PRODUCT_TESTING, 0,
                PLANNING, 1,

    CREDITS_WAIT, 12,

         PRODUCT_TESTING, 0,
          KEITA_NAKAMURA, 1,
         HIROTAKA_UEMURA, 2,
          HIROAKI_TAMURA, 3,
       NORIAKI_SAKAGUCHI, 4,

    CREDITS_WAIT, 12,

         PRODUCT_TESTING, 0,
    NCL_SUPER_MARIO_CLUB, 1,
             KENJI_SAIKI, 2,
            ATSUSHI_TADA, 3,
             MIYUKI_SATO, 4,

    CREDITS_WAIT, 12,

          SPECIAL_THANKS, 0,
        KIMIKO_NAKAMICHI, 1,
              AKITO_MORI, 2,

    CREDITS_WAIT, 12,

          SPECIAL_THANKS, 0,
           GAKUZI_NOMOTO, 1,
              AI_MASHIMA, 2,
         KUNIMI_KAWAMURA, 3,

    CREDITS_WAIT, 12,

          SPECIAL_THANKS, 0,
       MIKIHIRO_ISHIKAWA, 1,
      HIDEYUKI_HASHIMOTO, 2,

    CREDITS_WAIT, 12,

      EXECUTIVE_PRODUCER, 1,
        HIROSHI_YAMAUCHI, 2,

    CREDITS_WAIT, 12,

               COPYRIGHT, 1,

    CREDITS_WAIT, 9,

// Display "The End" graphic.
    CREDITS_THEEND,

    CREDITS_WAIT, 20,

    CREDITS_END
};
