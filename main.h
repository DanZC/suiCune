#include "home.h"

//#include "constants.h"

// SECTION "bank1", ROMX

//#include "engine/link/place_waiting_text.h"
//#include "engine/gfx/load_push_oam.h"
#include "engine/overworld/map_objects.h"
//#include "engine/menus/intro_menu.h"
//#include "engine/overworld/init_map.h"
//#include "engine/pokemon/learn.h"
//#include "engine/pokemon/correct_nick_errors.h"
//#include "engine/math/math.h"
//#include "data/items/attributes.h"
//#include "engine/overworld/npc_movement.h"
//#include "engine/events/happiness_egg.h"
//#include "engine/events/shuckle.h"
//#include "engine/events/haircut.h"

// SECTION "bank2", ROMX

//#include "engine/overworld/player_object.h"
//#include "engine/math/sine.h"
//#include "engine/predef.h"
//#include "engine/gfx/color.h"

// SECTION "bank3", ROMX

//#include "engine/events/checktime.h"
//#include "engine/events/specials.h"
//#include "engine/math/print_num.h"
//#include "engine/pokemon/health.h"
//#include "engine/events/overworld.h"
//#include "engine/items/items.h"
//#include "engine/overworld/player_step.h"
//#include "engine/battle/anim_hp_bar.h"
//#include "engine/pokemon/move_mon.h"
//#include "engine/pokemon/bills_pc_top.h"
//#include "engine/pokemon/breedmon_level_growth.h"
//#include "engine/events/bug_contest/caught_mon.h"
//#include "engine/items/item_effects.h"
//#include "engine/battle_anims/pokeball_wobble.h"
//#include "engine/pokemon/knows_move.h"

// SECTION "bank4", ROMX

//#include "engine/items/pack.h"
//#include "engine/overworld/time.h"
//#include "engine/items/tmhm2.h"
//#include "engine/menus/naming_screen.h"
//#include "engine/events/misc_scripts.h"
//#include "engine/events/heal_machine_anim.h"
//#include "engine/events/whiteout.h"
//#include "engine/events/forced_movement.h"
//#include "engine/events/itemfinder.h"
//#include "engine/menus/start_menu.h"
//#include "engine/pokemon/mon_menu.h"
//#include "engine/overworld/select_menu.h"
//#include "engine/events/elevator.h"
//#include "engine/events/bug_contest/contest.h"
//#include "engine/events/repel.h"
//#include "engine/events/hidden_item.h"
//#include "engine/events/std_collision.h"
//#include "engine/events/bug_contest/judging.h"
//#include "engine/events/pokerus/apply_pokerus_tick.h"
//#include "engine/events/bug_contest/contest_2.h"
//#include "engine/pokemon/correct_party_errors.h"
//#include "engine/math/get_square_root.h"

// SECTION "bank5", ROMX

//#include "engine/rtc/rtc.h"
//#include "engine/overworld/overworld.h"
//#include "engine/overworld/tile_events.h"
//#include "engine/menus/save.h"
//#include "engine/overworld/spawn_points.h"
//#include "engine/overworld/map_setup.h"
//#include "engine/events/pokecenter_pc.h"
//#include "engine/items/mart.h"
//#include "engine/events/money.h"
//#include "data/items/marts.h"
//#include "engine/events/mom.h"
//#include "engine/events/daycare.h"
//#include "engine/events/print_unown.h"
//#include "engine/events/print_photo.h"
//#include "engine/pokemon/breeding.h"

// SECTION "Roofs", ROMX

//#include "engine/tilesets/mapgroup_roofs.h"

// SECTION "Clock Reset", ROMX

//#include "engine/rtc/restart_clock.h"

// SECTION "bank9", ROMX

//#include "data/text_buffers.h"
//#include "engine/menus/menu.h"
//#include "engine/items/update_item_description.h"
//#include "engine/events/pokepic.h"
//#include "engine/overworld/map_objects_2.h"
//#include "engine/menus/scrolling_menu.h"
//#include "engine/items/switch_items.h"
//#include "engine/menus/menu_2.h"
//#include "engine/pokemon/mon_submenu.h"
//#include "engine/battle/menu.h"
//#include "engine/items/buy_sell_toss.h"
//#include "engine/menus/trainer_card.h"
//#include "engine/events/prof_oaks_pc.h"
//#include "engine/overworld/decorations.h"
//#include "engine/pokemon/level_up_happiness.h"
//#include "engine/battle/read_trainer_dvs.h"
//#include "engine/battle/returntobattle_useball.h"
//#include "engine/battle/consume_held_item.h"
//#include "data/moves/effects.h"
//#include "engine/events/kurt_selectquantity_interpretjoypad.h"

// SECTION "bankA", ROMX

//#include "engine/link/link.h"
//#include "engine/overworld/wildmons.h"
//#include "engine/battle/link_result.h"

// SECTION "bankB", ROMX

//#include "engine/battle/trainer_huds.h"
//#include "data/trainers/class_names.h"
//#include "engine/battle/ai/redundant.h"
//#include "engine/events/move_deleter.h"
//#include "engine/link/mystery_gift_2.h"
//#include "engine/items/tmhm.h"
//#include "engine/pokemon/print_move_description.h"
//#include "engine/events/pokerus/pokerus.h"
//#include "engine/battle/start_battle.h"
//#include "engine/gfx/place_graphic.h"

// SECTION "Effect Commands", ROMX

//#include "engine/battle/effect_commands.h"

// SECTION "Enemy Trainers", ROMX

//#include "engine/battle/ai/items.h"
//#include "engine/battle/ai/scoring.h"
//#include "engine/battle/read_trainer_attributes.h"
//#include "engine/battle/read_trainer_party.h"

// SECTION "Battle Core", ROMX

//#include "engine/battle/core.h"
//#include "data/battle/effect_command_pointers.h"

// SECTION "bank10", ROMX

//#include "engine/pokedex/pokedex.h"
//#include "data/moves/moves.h"
//#include "engine/pokemon/evolve.h"

// SECTION "bank11", ROMX

//#include "engine/events/fruit_trees.h"
//#include "engine/battle/ai/move.h"
//#include "engine/pokedex/pokedex_2.h"
//#include "engine/pokemon/mail.h"

// SECTION "Crystal Features 1", ROMX

//#include "engine/menus/init_gender.h"
//#include "engine/items/pack_kris.h"
//#include "engine/events/move_tutor.h"
//#include "engine/gfx/crystal_layouts.h"
//#include "engine/events/celebi.h"
//#include "engine/menus/main_menu.h"
//#include "mobile/mobile_menu.h"
//#include "engine/pokemon/search.h"
//#include "mobile/mobile_12_2.h"
//#include "engine/events/buena_menu.h"

// SECTION "bank13", ROMX

//#include "engine/tilesets/map_palettes.h"
//#include "gfx/tileset_palette_maps.h"
//#include "data/collision/collision_permissions.h"
//#include "engine/menus/empty_sram.h"
#include "engine/menus/savemenu_copytilemapatonce.h"
//#include "engine/events/checksave.h"
//#include "data/maps/scenes.h"
//#include "engine/overworld/load_map_part.h"
//#include "engine/phone/phonering_copytilemapatonce.h"

// SECTION "bank13_2", ROMX

//#include "engine/link/link_2.h"
//#include "engine/rtc/reset_password.h"
//#include "engine/menus/delete_save.h"
//#include "data/tilesets.h"
//#include "engine/smallflag.h"
//#include "engine/gfx/trademon_frontpic.h"
//#include "engine/events/pokerus/check_pokerus.h"
//#include "engine/events/lucky_number.h"
//#include "engine/pokemon/caught_data.h"
//#include "engine/pokemon/search2.h"
//#include "engine/pokemon/stats_screen.h"
//#include "engine/events/catch_tutorial.h"
//#include "engine/movie/evolution_animation.h"
//#include "engine/movie/init_hof_credits.h"
//#include "engine/events/battle_tower/get_trainer_class.h"
//#include "engine/battle/sliding_intro.h"
//#include "mobile/print_opp_message.h"
//#include "engine/battle/check_battle_scene.h"
//#include "engine/movie/gbc_only.h"
//#include "engine/events/poke_seer.h"

// SECTION "bank14", ROMX

//#include "engine/pokemon/party_menu.h"
//#include "engine/events/poisonstep.h"
//#include "engine/events/sweet_scent.h"
//#include "engine/events/squirtbottle.h"
//#include "engine/events/card_key.h"
//#include "engine/events/basement_key.h"
//#include "engine/events/sacred_ash.h"
//#include "engine/pokemon/tempmon.h"
//#include "engine/pokemon/types.h"
//#include "engine/battle/getgen1trainerclassname.h"
//#include "engine/pokemon/mon_stats.h"
//#include "engine/link/init_list.h"
//#include "engine/pokemon/experience.h"
//#include "engine/pokemon/switchpartymons.h"
//#include "engine/gfx/load_pics.h"
//#include "engine/pokemon/move_mon_wo_mail.h"
//#include "data/pokemon/base_stats.h"
//#include "data/pokemon/names.h"
//#include "data/pokemon/unused_pic_banks.h"

// SECTION "Crystal Phone Text", ROMX

//#include "data/phone/text/irwin_caller.h"
//#include "data/phone/text/arnie_caller.h"
//#include "data/phone/text/alan_caller.h"
//#include "data/phone/text/dana_caller.h"
//#include "data/phone/text/chad_caller.h"
//#include "data/phone/text/derek_caller.h"
//#include "data/phone/text/tully_caller.h"
//#include "data/phone/text/brent_caller.h"
//#include "data/phone/text/tiffany_caller.h"
//#include "data/phone/text/vance_caller.h"
//#include "data/phone/text/wilton_caller.h"
//#include "data/phone/text/kenji_caller.h"
//#include "data/phone/text/parry_caller.h"
//#include "data/phone/text/erin_caller.h"

// SECTION "bank20", ROMX

//#include "engine/overworld/player_movement.h"
//#include "engine/events/engine_flags.h"
//#include "engine/overworld/variables.h"
//#include "data/text/battle.h"
//#include "engine/debug/color_picker.h"

// SECTION "bank21", ROMX

//#include "engine/printer/printer_serial.h"
//#include "engine/printer/printer.h"
//#include "gfx/battle_anims.h"
//#include "engine/events/halloffame.h"

// SECTION "Crystal Features 2", ROMX

//#include "engine/events/kurt.h"
//#include "engine/gfx/player_gfx.h"
//#include "mobile/mobile_22.h"
//#include "engine/events/unown_walls.h"
//#include "engine/events/buena.h"
//#include "engine/events/dratini.h"
//#include "engine/events/battle_tower/rules.h"
//#include "mobile/mobile_22_2.h"

// SECTION "bank23", ROMX

//#include "engine/tilesets/timeofday_pals.h"
//#include "engine/battle/battle_transition.h"
//#include "engine/events/field_moves.h"
//#include "engine/events/magnet_train.h"
//#include "engine/battle/battlestart_copytilemapatonce.h"
//#include "engine/gfx/sprites.h"
//#include "engine/gfx/mon_icons.h"

// SECTION "bank24", ROMX

//#include "engine/phone/phone.h"
//#include "engine/rtc/timeset.h"
//#include "engine/pokegear/pokegear.h"
//#include "engine/events/fish.h"
//#include "engine/games/slot_machine.h"

// SECTION "Phone Scripts 1", ROMX

//#include "engine/phone/scripts/generic_caller.h"
//#include "engine/phone/scripts/jack_gossip.h"
//#include "engine/phone/scripts/liz_gossip.h"
//#include "engine/phone/scripts/chad_gossip.h"
//#include "engine/phone/scripts/brent_gossip.h"
//#include "engine/phone/scripts/irwin_gossip.h"
//#include "engine/phone/scripts/hangups.h"
//#include "engine/phone/scripts/reminders.h"
//#include "engine/phone/scripts/hangups_2.h"
//#include "engine/phone/scripts/reminders_2.h"
//#include "engine/phone/scripts/bike_shop.h"
//#include "engine/phone/scripts/buena.h"

// SECTION "Phone Text", ROMX

//#include "data/phone/text/anthony_overworld.h"
//#include "data/phone/text/todd_overworld.h"
//#include "data/phone/text/gina_overworld.h"
//#include "data/phone/text/irwin_overworld.h"
//#include "data/phone/text/arnie_overworld.h"
//#include "data/phone/text/alan_overworld.h"
//#include "data/phone/text/dana_overworld.h"
//#include "data/phone/text/chad_overworld.h"
//#include "data/phone/text/derek_overworld.h"
//#include "data/phone/text/tully_overworld.h"
//#include "data/phone/text/brent_overworld.h"
//#include "data/phone/text/tiffany_overworld.h"
//#include "data/phone/text/vance_overworld.h"
//#include "data/phone/text/wilton_overworld.h"
//#include "data/phone/text/kenji_overworld.h"
//#include "data/phone/text/parry_overworld.h"
//#include "data/phone/text/erin_overworld.h"

// SECTION "bank2E", ROMX

//#include "engine/events/map_name_sign.h"
//#include "engine/events/checkforhiddenitems.h"
//#include "engine/events/treemons.h"
//#include "engine/events/fishing_gfx.h"
//#include "engine/pokegear/radio.h"
//#include "engine/pokemon/mail_2.h"

// SECTION "Phone Scripts 2", ROMX

//#include "engine/events/std_scripts.h"
//#include "engine/phone/scripts/unused.h"
//#include "engine/phone/scripts/mom.h"
//#include "engine/phone/scripts/bill.h"
//#include "engine/phone/scripts/elm.h"
//#include "engine/phone/scripts/jack.h"
//#include "engine/phone/scripts/beverly.h"
//#include "engine/phone/scripts/huey.h"
//#include "engine/phone/scripts/gaven.h"
//#include "engine/phone/scripts/beth.h"
//#include "engine/phone/scripts/jose.h"
//#include "engine/phone/scripts/reena.h"
//#include "engine/phone/scripts/joey.h"
//#include "engine/phone/scripts/wade.h"
//#include "engine/phone/scripts/ralph.h"
//#include "engine/phone/scripts/liz.h"
//#include "engine/phone/scripts/anthony.h"
//#include "engine/phone/scripts/todd.h"
//#include "engine/phone/scripts/gina.h"
//#include "engine/phone/scripts/irwin.h"
//#include "engine/phone/scripts/arnie.h"
//#include "engine/phone/scripts/alan.h"
//#include "engine/phone/scripts/dana.h"
//#include "engine/phone/scripts/chad.h"
//#include "engine/phone/scripts/derek.h"
//#include "engine/phone/scripts/tully.h"
//#include "engine/phone/scripts/brent.h"
//#include "engine/phone/scripts/tiffany.h"
//#include "engine/phone/scripts/vance.h"
//#include "engine/phone/scripts/wilton.h"
//#include "engine/phone/scripts/kenji.h"
//#include "engine/phone/scripts/parry.h"
//#include "engine/phone/scripts/erin.h"
//#include "engine/phone/scripts/generic_callee.h"
//#include "engine/events/trainer_scripts.h"

// SECTION "bank32", ROMX

#include "engine/battle_anims/bg_effects.h"
//#include "data/moves/animations.h"
//#include "engine/events/poisonstep_pals.h"

// SECTION "Move Animations", ROMX

//#include "engine/events/bug_contest/display_stats.h"
//#include "engine/battle_anims/anim_commands.h"
//#include "engine/battle_anims/core.h"
#include "engine/battle_anims/functions.h"
//#include "engine/battle_anims/helpers.h"

// SECTION "Pic Animations 1", ROMX

//#include "engine/gfx/pic_animation.h"
//#include "gfx/pokemon/anim_pointers.h"
//#include "gfx/pokemon/anims.h"
//#include "gfx/pokemon/idle_pointers.h"
//#include "gfx/pokemon/idles.h"
//#include "gfx/pokemon/unown_anim_pointers.h"
//#include "gfx/pokemon/unown_anims.h"
//#include "gfx/pokemon/unown_idle_pointers.h"
//#include "gfx/pokemon/unown_idles.h"
//#include "gfx/pokemon/bitmask_pointers.h"
//#include "gfx/pokemon/bitmasks.h"
//#include "gfx/pokemon/unown_bitmask_pointers.h"
//#include "gfx/pokemon/unown_bitmasks.h"

// SECTION "Pic Animations 2", ROMX

//#include "gfx/pokemon/frame_pointers.h"
//#include "gfx/pokemon/kanto_frames.h"

// SECTION "Pic Animations 3", ROMX

//#include "gfx/pokemon/johto_frames.h"
//#include "gfx/pokemon/unown_frame_pointers.h"
//#include "gfx/pokemon/unown_frames.h"

// SECTION "bank38", ROMX

//#include "engine/events/print_unown_2.h"
//#include "engine/games/card_flip.h"
//#include "engine/games/unown_puzzle.h"
//#include "engine/games/memory_game.h"
//#include "engine/pokemon/bills_pc.h"

// SECTION "bank39", ROMX

//#include "engine/menus/options_menu.h"
//#include "engine/movie/splash.h"
//#include "engine/movie/intro.h"

// SECTION "Audio", ROMX

#include "audio.h"

// SECTION "bank3E", ROMX

//#include "engine/gfx/load_font.h"
//#include "engine/link/time_capsule.h"
//#include "engine/events/name_rater.h"
//#include "engine/events/play_slow_cry.h"
//#include "engine/pokedex/new_pokedex_entry.h"
//#include "engine/link/time_capsule_2.h"
//#include "engine/pokedex/unown_dex.h"
//#include "engine/events/magikarp.h"
//#include "engine/battle/hidden_power.h"
//#include "engine/battle/misc.h"

// SECTION "bank3F", ROMX

//#include "engine/tilesets/tileset_anims.h"
//#include "engine/events/npc_trade.h"
//#include "engine/events/mom_phone.h"

// SECTION "mobile40", ROMX

//#include "mobile/mobile_40.h"

// SECTION "bank41", ROMX

#include "engine/gfx/dma_transfer.h"
//#include "gfx/emotes.h"
//#include "engine/overworld/warp_connection.h"
//#include "engine/link/mystery_gift.h"
//#include "engine/battle/used_move_text.h"
//#include "mobile/mobile_41.h"
//#include "engine/gfx/load_overworld_font.h"

// SECTION "mobile42", ROMX

//#include "mobile/mobile_42.h"

// SECTION "Title", ROMX

//#include "engine/movie/unused_title.h"
//#include "engine/movie/title.h"

// SECTION "mobile45", ROMX

//#include "mobile/mobile_45.h"
//#include "mobile/mobile_45_sprite_engine.h"
//#include "mobile/mobile_45_2.h"
//#include "mobile/mobile_45_stadium.h"

// SECTION "mobile46", ROMX

//#include "mobile/mobile_46.h"

// SECTION "Battle Tower", ROMX

//#include "engine/events/battle_tower/trainer_text.h"

// SECTION "bank5B", ROMX

//#include "mobile/mobile_5b.h"
//#include "engine/link/link_trade.h"

// SECTION "mobile5C", ROMX

//#include "mobile/mobile_5c.h"

// SECTION "Crystal Phone Text 2", ROMX

//#include "data/phone/text/bike_shop.h"
//#include "data/phone/text/jack_caller.h"
//#include "data/phone/text/beverly_caller.h"
//#include "data/phone/text/huey_caller.h"
//#include "data/phone/text/gaven_caller.h"
//#include "data/phone/text/beth_caller.h"
//#include "data/phone/text/jose_caller.h"
//#include "data/phone/text/reena_caller.h"
//#include "data/phone/text/joey_caller.h"
//#include "data/phone/text/wade_caller.h"
//#include "data/phone/text/ralph_caller.h"
//#include "data/phone/text/liz_caller.h"
//#include "data/phone/text/anthony_caller.h"
//#include "data/phone/text/todd_caller.h"
//#include "data/phone/text/gina_caller.h"

// SECTION "UpdateBattleHUDs", ROMX

//#include "engine/battle/update_battle_huds.h"

// SECTION "mobile5E", ROMX

//#include "mobile/mobile_5e.h"

// SECTION "mobile5F", ROMX

//#include "mobile/mobile_5f.h"

// SECTION "Phone Text 2", ROMX

//#include "data/text/std_text.h"
//#include "data/phone/text/jack_overworld.h"
//#include "data/phone/text/beverly_overworld.h"
//#include "data/phone/text/huey_overworld.h"
//#include "data/phone/text/gaven_overworld.h"
//#include "data/phone/text/beth_overworld.h"
//#include "data/phone/text/jose_overworld.h"
//#include "data/phone/text/reena_overworld.h"
//#include "data/phone/text/joey_overworld.h"
//#include "data/phone/text/wade_overworld.h"
//#include "data/phone/text/ralph_overworld.h"
//#include "data/phone/text/liz_overworld.h"

// SECTION "Special Phone Text", ROMX

//#include "data/phone/text/mom.h"
//#include "data/phone/text/bill.h"
//#include "data/phone/text/elm.h"
//#include "data/phone/text/jack_callee.h"
//#include "data/phone/text/beverly_callee.h"
//#include "data/phone/text/huey_callee.h"
//#include "data/phone/text/unknown_callee.h"
//#include "data/phone/text/gaven_callee.h"
//#include "data/phone/text/beth_callee.h"
//#include "data/phone/text/jose_callee.h"
//#include "data/phone/text/reena_callee.h"
//#include "data/phone/text/joey_callee.h"
//#include "data/phone/text/wade_callee.h"
//#include "data/phone/text/ralph_callee.h"
//#include "data/phone/text/liz_callee.h"
//#include "data/phone/text/anthony_callee.h"
//#include "data/phone/text/todd_callee.h"
//#include "data/phone/text/gina_callee.h"
//#include "data/phone/text/irwin_callee.h"
//#include "data/phone/text/arnie_callee.h"
//#include "data/phone/text/alan_callee.h"
//#include "data/phone/text/dana_callee.h"
//#include "data/phone/text/chad_callee.h"
//#include "data/phone/text/derek_callee.h"
//#include "data/phone/text/tully_callee.h"
//#include "data/phone/text/brent_callee.h"
//#include "data/phone/text/tiffany_callee.h"
//#include "data/phone/text/vance_callee.h"
//#include "data/phone/text/wilton_callee.h"
//#include "data/phone/text/kenji_callee.h"
//#include "data/phone/text/parry_callee.h"
//#include "data/phone/text/erin_callee.h"
//#include "data/phone/text/unused.h"

// SECTION "Miscellaneous Text", ROMX

//#include "data/items/names.h"
//#include "engine/items/print_item_description.h"
//#include "data/moves/names.h"
//#include "engine/overworld/landmarks.h"

// SECTION "Print Party", ROMX

//#include "engine/printer/print_party.h"

// SECTION "bank77", ROMX

//#include "engine/rtc/print_hours_mins.h"
//#include "engine/events/diploma.h"
//#include "engine/pokedex/pokedex_3.h"
//#include "engine/events/catch_tutorial_input.h"
//#include "engine/pokegear/townmap_convertlinebreakcharacters.h"

// SECTION "European Mail", ROMX

//#include "engine/pokemon/european_mail.h"

// SECTION "Debug Room", ROMX

#if _DEBUG
//#include "engine/debug/debug_room.h"
#endif

// SECTION "Battle Tower Text", ROMX

//#include "data/battle_tower/trainer_text.h"

// SECTION "Battle Tower Trainer Data", ROMX

//#include "data/battle_tower/unknown.h"

// SECTION "Mobile News Data", ROMX

//#include "mobile/news/news.h"

// SECTION "Crystal Events", ROMX

//#include "engine/events/battle_tower/load_trainer.h"
//#include "engine/events/odd_egg.h"

// SECTION "Stadium 2 Checksums", ROMX[$7DE0], BANK[$7F]

// The end of the ROM is taken up by checksums of the content, apparently used
// by Pokémon Stadium 2 due to the checksums' "N64PS3" header. (In Japan,
// Pokémon Stadium Gold and Silver was the third Stadium release for N64.)
// This //SECTION reserves space for those checksums.
// If it is removed, also remove the "tools/stadium" command in the Makefile.
