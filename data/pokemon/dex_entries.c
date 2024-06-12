#include "../../constants.h"

static const struct DexEntry BulbasaurPokedexEntry = {
    .category = "SEED@", // species name
    .height = 204, .weight = 150, // height, weight
    .description = "While it is young,"  
        t_next "it uses the" 
        t_next "nutrients that are" 
        t_page "stored in the" 
        t_next "seeds on its back" 
        t_next "in order to grow.@"
};
static const struct DexEntry IvysaurPokedexEntry = {
    .category = "SEED@", // species name
    .height = 303, .weight = 290, // height, weight
    .description = "The bulb on its"  
        t_next "back grows as it" 
        t_next "absorbs nutrients." 
        t_page "The bulb gives off" 
        t_next "a pleasant aroma" 
        t_next "when it blooms.@" 
};
static const struct DexEntry VenusaurPokedexEntry = {
    .category = "SEED@", // species name
    .height = 607, .weight = 2210, // height, weight
    .description = "As it warms it-"  
        t_next "self and absorbs" 
        t_next "the sunlight, its" 
        t_page "flower petals" 
        t_next "release a pleasant" 
        t_next "fragrance.@" 
};
static const struct DexEntry CharmanderPokedexEntry = {
    .category = "LIZARD@", // species name
    .height = 200, .weight = 190, // height, weight
    .description = "If it's healthy,"  
        t_next "the flame on the" 
        t_next "tip of its tail" 
        t_page "will burn vigor-" 
        t_next "ously, even if it" 
        t_next "gets a bit wet.@" 
};
static const struct DexEntry CharmeleonPokedexEntry = {
    .category = "FLAME@", // species name
    .height = 307, .weight = 420, // height, weight
    .description = "If it becomes"  
        t_next "agitated during" 
        t_next "battle, it spouts" 
        t_page "intense flames," 
        t_next "incinerating its" 
        t_next "surroundings.@" 
};
static const struct DexEntry CharizardPokedexEntry = {
    .category = "FLAME@", // species name
    .height = 507, .weight = 2000, // height, weight
    .description = "It uses its wings"  
        t_next "to fly high. The" 
        t_next "temperature of its" 
        t_page "fire increases as" 
        t_next "it gains exper-" 
        t_next "ience in battle.@" 
};
static const struct DexEntry SquirtlePokedexEntry = {
    .category = "TINYTURTLE@", // species name
    .height = 108, .weight = 200, // height, weight
    .description = "When it feels"  
        t_next "threatened, it" 
        t_next "draws its legs" 
        t_page "inside its shell" 
        t_next "and sprays water" 
        t_next "from its mouth.@" 
};
static const struct DexEntry WartortlePokedexEntry = {
    .category = "TURTLE@", // species name
    .height = 303, .weight = 500, // height, weight
    .description = "Its long, furry"  
        t_next "tail is a symbol" 
        t_next "of longevity," 
        t_page "making it quite" 
        t_next "popular among" 
        t_next "older people.@" 
};
static const struct DexEntry BlastoisePokedexEntry = {
    .category = "SHELLFISH@", // species name
    .height = 503, .weight = 1890, // height, weight
    .description = "It firmly plants"  
        t_next "its feet on the" 
        t_next "ground before" 
        t_page "shooting water" 
        t_next "from the jets on" 
        t_next "its back.@" 
};
static const struct DexEntry CaterpiePokedexEntry = {
    .category = "WORM@", // species name
    .height = 100, .weight = 60, // height, weight
    .description = "It crawls into"  
        t_next "foliage where it" 
        t_next "camouflages itself" 
        t_page "among leaves that" 
        t_next "are the same color" 
        t_next "as its body.@" 
};
static const struct DexEntry MetapodPokedexEntry = {
    .category = "COCOON@", // species name
    .height = 204, .weight = 220, // height, weight
    .description = "This is its pre-"  
        t_next "evolved form. At" 
        t_next "this stage, it can" 
        t_page "only harden, so it" 
        t_next "remains motionless" 
        t_next "to avoid attack.@" 
};
static const struct DexEntry ButterfreePokedexEntry = {
    .category = "BUTTERFLY@", // species name
    .height = 307, .weight = 710, // height, weight
    .description = "It flits from"  
        t_next "flower to flower," 
        t_next "collecting honey." 
        t_page "It can even" 
        t_next "identify distant" 
        t_next "flowers in bloom.@" 
};
static const struct DexEntry WeedlePokedexEntry = {
    .category = "HAIRY BUG@", // species name
    .height = 100, .weight = 70, // height, weight
    .description = "The barb on top of"  
        t_next "its head secretes" 
        t_next "a strong poison." 
        t_page "It uses this toxic" 
        t_next "barb to protect" 
        t_next "itself.@" 
};
static const struct DexEntry KakunaPokedexEntry = {
    .category = "COCOON@", // species name
    .height = 200, .weight = 220, // height, weight
    .description = "Nearly incapable"  
        t_next "of movement, it" 
        t_next "leans against" 
        t_page "stout trees while" 
        t_next "waiting for its" 
        t_next "evolution.@" 
};
static const struct DexEntry BeedrillPokedexEntry = {
    .category = "POISON BEE@", // species name
    .height = 303, .weight = 650, // height, weight
    .description = "It uses sharp,"  
        t_next "poisonous stings" 
        t_next "to defeat prey," 
        t_page "then takes the" 
        t_next "victim back to its" 
        t_next "nest for food.@" 
};
static const struct DexEntry PidgeyPokedexEntry = {
    .category = "TINY BIRD@", // species name
    .height = 100, .weight = 40, // height, weight
    .description = "It rapidly flaps"  
        t_next "its wings in the" 
        t_next "grass, stirring up" 
        t_page "a dust cloud that" 
        t_next "drives insect prey" 
        t_next "out into the open.@" 
};
static const struct DexEntry PidgeottoPokedexEntry = {
    .category = "BIRD@", // species name
    .height = 307, .weight = 660, // height, weight
    .description = "It slowly flies in"  
        t_next "a circular pat-" 
        t_next "tern, all the" 
        t_page "while keeping a" 
        t_next "sharp lookout for" 
        t_next "prey.@" 
};
static const struct DexEntry PidgeotPokedexEntry = {
    .category = "BIRD@", // species name
    .height = 411, .weight = 870, // height, weight
    .description = "Its outstanding"  
        t_next "vision allows it" 
        t_next "to spot splashing" 
        t_page "MAGIKARP, even" 
        t_next "while flying at" 
        t_next "3300 feet.@" 
};
static const struct DexEntry RattataPokedexEntry = {
    .category = "RAT@", // species name
    .height = 100, .weight = 80, // height, weight
    .description = "This #MON's"  
        t_next "impressive vital-" 
        t_next "ity allows it to" 
        t_page "live anywhere. It" 
        t_next "also multiplies" 
        t_next "very quickly.@" 
};
static const struct DexEntry RaticatePokedexEntry = {
    .category = "RAT@", // species name
    .height = 204, .weight = 410, // height, weight
    .description = "The webs on its"  
        t_next "hind legs enable" 
        t_next "it to cross" 
        t_page "rivers. It search-" 
        t_next "es wide areas for" 
        t_next "food.@" 
};
static const struct DexEntry SpearowPokedexEntry = {
    .category = "TINY BIRD@", // species name
    .height = 100, .weight = 40, // height, weight
    .description = "To protect its"  
        t_next "territory, it" 
        t_next "flies around" 
        t_page "ceaselessly," 
        t_next "making high-" 
        t_next "pitched cries.@" 
};
static const struct DexEntry FearowPokedexEntry = {
    .category = "BEAK@", // species name
    .height = 311, .weight = 840, // height, weight
    .description = "It uses its long"  
        t_next "beak to attack. It" 
        t_next "has a surprisingly" 
        t_page "long reach, so it" 
        t_next "must be treated" 
        t_next "with caution.@" 
};
static const struct DexEntry EkansPokedexEntry = {
    .category = "SNAKE@", // species name
    .height = 607, .weight = 150, // height, weight
    .description = "It flutters the"  
        t_next "tip of its tongue" 
        t_next "to seek out the" 
        t_page "scent of prey," 
        t_next "then swallows the" 
        t_next "prey whole.@" 
};
static const struct DexEntry ArbokPokedexEntry = {
    .category = "COBRA@", // species name
    .height = 1106, .weight = 1430, // height, weight
    .description = "To intimidate"  
        t_next "foes, it spreads" 
        t_next "its chest wide and" 
        t_page "makes eerie sounds" 
        t_next "by expelling air" 
        t_next "from its mouth.@" 
};
static const struct DexEntry PikachuPokedexEntry = {
    .category = "MOUSE@", // species name
    .height = 104, .weight = 130, // height, weight
    .description = "When it is anger-"  
        t_next "ed, it immediately" 
        t_next "discharges the" 
        t_page "energy stored in" 
        t_next "the pouches in its" 
        t_next "cheeks.@" 
};
static const struct DexEntry RaichuPokedexEntry = {
    .category = "MOUSE@", // species name
    .height = 207, .weight = 660, // height, weight
    .description = "If its electric"  
        t_next "pouches run empty," 
        t_next "it raises its tail" 
        t_page "to gather electri-" 
        t_next "city from the" 
        t_next "atmosphere.@" 
};
static const struct DexEntry SandshrewPokedexEntry = {
    .category = "MOUSE@", // species name
    .height = 200, .weight = 260, // height, weight
    .description = "It prefers dry,"  
        t_next "sandy places" 
        t_next "because it uses" 
        t_page "the sand to" 
        t_next "protect itself" 
        t_next "when threatened.@" 
};
static const struct DexEntry SandslashPokedexEntry = {
    .category = "MOUSE@", // species name
    .height = 303, .weight = 650, // height, weight
    .description = "Adept at climbing"  
        t_next "trees, it rolls" 
        t_next "into a spiny ball," 
        t_page "then attacks its" 
        t_next "enemies from" 
        t_next "above.@" 
};
static const struct DexEntry NidoranFPokedexEntry = {
    .category = "POISON PIN@", // species name
    .height = 104, .weight = 150, // height, weight
    .description = "Small and very"  
        t_next "docile, it pro-" 
        t_next "tects itself with" 
        t_page "its small, poison-" 
        t_next "ous horn when" 
        t_next "attacked.@" 
};
static const struct DexEntry NidorinaPokedexEntry = {
    .category = "POISON PIN@", // species name
    .height = 207, .weight = 440, // height, weight
    .description = "It has a docile"  
        t_next "nature. If it is" 
        t_next "threatened with" 
        t_page "attack, it raises" 
        t_next "the barbs that are" 
        t_next "all over its body.@" 
};
static const struct DexEntry NidoqueenPokedexEntry = {
    .category = "DRILL@", // species name
    .height = 403, .weight = 1320, // height, weight
    .description = "The hard scales"  
        t_next "that cover its" 
        t_next "strong body serve" 
        t_page "as excellent" 
        t_next "protection from" 
        t_next "any attack.@" 
};
static const struct DexEntry NidoranMPokedexEntry = {
    .category = "POISON PIN@", // species name
    .height = 108, .weight = 200, // height, weight
    .description = "It constantly"  
        t_next "moves its large" 
        t_next "ears in many" 
        t_page "directions in" 
        t_next "order to detect" 
        t_next "danger right away.@" 
};
static const struct DexEntry NidorinoPokedexEntry = {
    .category = "POISON PIN@", // species name
    .height = 211, .weight = 430, // height, weight
    .description = "It is easily"  
        t_next "agitated and uses" 
        t_next "its horn for" 
        t_page "offense as soon as" 
        t_next "it notices an" 
        t_next "attacker.@" 
};
static const struct DexEntry NidokingPokedexEntry = {
    .category = "DRILL@", // species name
    .height = 407, .weight = 1370, // height, weight
    .description = "It uses its thick"  
        t_next "arms, legs and" 
        t_next "tail to attack" 
        t_page "forcefully. Melee" 
        t_next "combat is its" 
        t_next "specialty.@" 
};
static const struct DexEntry ClefairyPokedexEntry = {
    .category = "FAIRY@", // species name
    .height = 200, .weight = 170, // height, weight
    .description = "Though rarely"  
        t_next "seen, it becomes" 
        t_next "easier to spot," 
        t_page "for some reason," 
        t_next "on the night of a " 
        t_next "full moon.@" 
};
static const struct DexEntry ClefablePokedexEntry = {
    .category = "FAIRY@", // species name
    .height = 403, .weight = 880, // height, weight
    .description = "Said to live in"  
        t_next "quiet, remote" 
        t_next "mountains, this" 
        t_page "type of fairy has" 
        t_next "a strong aversion" 
        t_next "to being seen.@" 
};
static const struct DexEntry VulpixPokedexEntry = {
    .category = "FOX@", // species name
    .height = 200, .weight = 220, // height, weight
    .description = "As its body grows"  
        t_next "larger, its six" 
        t_next "warm tails become" 
        t_page "more beautiful," 
        t_next "with a more luxur-" 
        t_next "ious coat of fur.@" 
};
static const struct DexEntry NinetalesPokedexEntry = {
    .category = "FOX@", // species name
    .height = 307, .weight = 440, // height, weight
    .description = "It is said to live"  
        t_next "a thousand years," 
        t_next "and each of its" 
        t_page "tails is loaded" 
        t_next "with supernatural" 
        t_next "powers.@" 
};
static const struct DexEntry JigglypuffPokedexEntry = {
    .category = "BALLOON@", // species name
    .height = 108, .weight = 120, // height, weight
    .description = "It rolls its cute"  
        t_next "eyes as it sings a" 
        t_next "soothing lullaby." 
        t_page "Its gentle song" 
        t_next "puts anyone who" 
        t_next "hears it to sleep.@" 
};
static const struct DexEntry WigglytuffPokedexEntry = {
    .category = "BALLOON@", // species name
    .height = 303, .weight = 260, // height, weight
    .description = "The rich, fluffy"  
        t_next "fur that covers" 
        t_next "its body feels so" 
        t_page "good that anyone" 
        t_next "who feels it can't" 
        t_next "stop touching it.@" 
};
static const struct DexEntry ZubatPokedexEntry = {
    .category = "BAT@", // species name
    .height = 207, .weight = 170, // height, weight
    .description = "During the day, it"  
        t_next "gathers with" 
        t_next "others and hangs" 
        t_page "from the ceilings" 
        t_next "of old buildings" 
        t_next "and caves.@" 
};
static const struct DexEntry GolbatPokedexEntry = {
    .category = "BAT@", // species name
    .height = 503, .weight = 1210, // height, weight
    .description = "When it plunges"  
        t_next "its fangs into its" 
        t_next "prey, it instantly" 
        t_page "draws and gulps" 
        t_next "down more than ten" 
        t_next "ounces of blood.@" 
};
static const struct DexEntry OddishPokedexEntry = {
    .category = "WEED@", // species name
    .height = 108, .weight = 120, // height, weight
    .description = "During the day, it"  
        t_next "stays in the cold" 
        t_next "underground to" 
        t_page "avoid the sun." 
        t_next "It grows by bath-" 
        t_next "ing in moonlight.@" 
};
static const struct DexEntry GloomPokedexEntry = {
    .category = "WEED@", // species name
    .height = 207, .weight = 190, // height, weight
    .description = "The smell from its"  
        t_next "drool-like syrup" 
        t_next "and the pollen on" 
        t_page "its petals is so" 
        t_next "bad, it may make" 
        t_next "opponents faint.@" 
};
static const struct DexEntry VileplumePokedexEntry = {
    .category = "FLOWER@", // species name
    .height = 311, .weight = 410, // height, weight
    .description = "By shaking its big"  
        t_next "petals, it scat-" 
        t_next "ters toxic pollen" 
        t_page "into the air," 
        t_next "turning the air" 
        t_next "yellow.@" 
};
static const struct DexEntry ParasPokedexEntry = {
    .category = "MUSHROOM@", // species name
    .height = 100, .weight = 120, // height, weight
    .description = "The tochukaso"  
        t_next "growing on this" 
        t_next "#MON's back" 
        t_page "orders it to" 
        t_next "extract juice from" 
        t_next "tree trunks.@" 
};
static const struct DexEntry ParasectPokedexEntry = {
    .category = "MUSHROOM@", // species name
    .height = 303, .weight = 650, // height, weight
    .description = "When nothing's"  
        t_next "left to extract" 
        t_next "from the bug, the" 
        t_page "mushrooms on its" 
        t_next "back leave spores" 
        t_next "on the bug's egg.@" 
};
static const struct DexEntry VenonatPokedexEntry = {
    .category = "INSECT@", // species name
    .height = 303, .weight = 660, // height, weight
    .description = "The small bugs it"  
        t_next "eats appear only" 
        t_next "at night, so it" 
        t_page "sleeps in a hole" 
        t_next "in a tree until" 
        t_next "night falls.@" 
};
static const struct DexEntry VenomothPokedexEntry = {
    .category = "POISONMOTH@", // species name
    .height = 411, .weight = 280, // height, weight
    .description = "The scales it"  
        t_next "scatters will" 
        t_next "paralyze anyone" 
        t_page "who touches them," 
        t_next "making that person" 
        t_next "unable to stand.@" 
};
static const struct DexEntry DiglettPokedexEntry = {
    .category = "MOLE@", // species name
    .height = 8, .weight = 20, // height, weight
    .description = "It digs under-"  
        t_next "ground and chews" 
        t_next "on tree roots," 
        t_page "sticking its head" 
        t_next "out only when the" 
        t_next "sun isn't bright.@" 
};
static const struct DexEntry DugtrioPokedexEntry = {
    .category = "MOLE@", // species name
    .height = 204, .weight = 730, // height, weight
    .description = "These DIGLETT"  
        t_next "triplets dig over" 
        t_next "60 miles below sea" 
        t_page "level. No one" 
        t_next "knows what it's" 
        t_next "like underground.@" 
};
static const struct DexEntry MeowthPokedexEntry = {
    .category = "SCRATCHCAT@", // species name
    .height = 104, .weight = 90, // height, weight
    .description = "It loves things"  
        t_next "that sparkle. When" 
        t_next "it sees a shiny" 
        t_page "object, the gold" 
        t_next "coin on its head" 
        t_next "shines too.@" 
};
static const struct DexEntry PersianPokedexEntry = {
    .category = "CLASSY CAT@", // species name
    .height = 303, .weight = 710, // height, weight
    .description = "Behind its lithe,"  
        t_next "elegant appearance" 
        t_next "lies a barbaric" 
        t_page "side. It will tear" 
        t_next "apart its prey on" 
        t_next "a mere whim.@" 
};
static const struct DexEntry PsyduckPokedexEntry = {
    .category = "DUCK@", // species name
    .height = 207, .weight = 430, // height, weight
    .description = "The only time it"  
        t_next "can use its psy-" 
        t_next "chic power is when" 
        t_page "its sleeping brain" 
        t_next "cells happen to" 
        t_next "wake.@" 
};
static const struct DexEntry GolduckPokedexEntry = {
    .category = "DUCK@", // species name
    .height = 507, .weight = 1690, // height, weight
    .description = "It swims grace-"  
        t_next "fully along on the" 
        t_next "quiet, slow-moving" 
        t_page "rivers and lakes" 
        t_next "of which it is so" 
        t_next "fond.@" 
};
static const struct DexEntry MankeyPokedexEntry = {
    .category = "PIG MONKEY@", // species name
    .height = 108, .weight = 620, // height, weight
    .description = "It lives in groups"  
        t_next "in the treetops." 
        t_next "If it loses sight" 
        t_page "of its group, it" 
        t_next "becomes infuriated" 
        t_next "by its loneliness.@" 
};
static const struct DexEntry PrimeapePokedexEntry = {
    .category = "PIG MONKEY@", // species name
    .height = 303, .weight = 710, // height, weight
    .description = "It will beat up"  
        t_next "anyone who makes" 
        t_next "it mad, even if it" 
        t_page "has to chase them" 
        t_next "until the end of" 
        t_next "the world.@" 
};
static const struct DexEntry GrowlithePokedexEntry = {
    .category = "PUPPY@", // species name
    .height = 204, .weight = 420, // height, weight
    .description = "It controls a big"  
        t_next "territory. If it" 
        t_next "detects an unknown" 
        t_page "smell, it roars" 
        t_next "loudly to force" 
        t_next "out the intruder.@" 
};
static const struct DexEntry ArcaninePokedexEntry = {
    .category = "LEGENDARY@", // species name
    .height = 603, .weight = 3420, // height, weight
    .description = "An ancient picture"  
        t_next "scroll shows that" 
        t_next "people were" 
        t_page "attracted to its" 
        t_next "movement as it ran" 
        t_next "through prairies.@" 
};
static const struct DexEntry PoliwagPokedexEntry = {
    .category = "TADPOLE@", // species name
    .height = 200, .weight = 270, // height, weight
    .description = "The swirl on its"  
        t_next "belly is its" 
        t_next "insides showing" 
        t_page "through the skin." 
        t_next "It looks clearer" 
        t_next "after it eats.@" 
};
static const struct DexEntry PoliwhirlPokedexEntry = {
    .category = "TADPOLE@", // species name
    .height = 303, .weight = 440, // height, weight
    .description = "Though it is"  
        t_next "skilled at walk-" 
        t_next "ing, it prefers to" 
        t_page "live underwater" 
        t_next "where there is" 
        t_next "less danger.@" 
};
static const struct DexEntry PoliwrathPokedexEntry = {
    .category = "TADPOLE@", // species name
    .height = 403, .weight = 1190, // height, weight
    .description = "It can use its"  
        t_next "well-developed" 
        t_next "arms and legs to" 
        t_page "run on the surface" 
        t_next "of the water for a" 
        t_next "split second.@" 
};
static const struct DexEntry AbraPokedexEntry = {
    .category = "PSI@", // species name
    .height = 211, .weight = 430, // height, weight
    .description = "It hypnotizes"  
        t_next "itself so that it" 
        t_next "can teleport away" 
        t_page "when it senses" 
        t_next "danger, even" 
        t_next "if it is asleep.@" 
};
static const struct DexEntry KadabraPokedexEntry = {
    .category = "PSI@", // species name
    .height = 403, .weight = 1250, // height, weight
    .description = "When it closes its"  
        t_next "eyes, twice as" 
        t_next "many alpha parti-" 
        t_page "cles come out of" 
        t_next "the surface of its" 
        t_next "body.@" 
};
static const struct DexEntry AlakazamPokedexEntry = {
    .category = "PSI@", // species name
    .height = 411, .weight = 1060, // height, weight
    .description = "It has an IQ of"  
        t_next "5000. It calcu-" 
        t_next "lates many things" 
        t_page "in order to gain" 
        t_next "the edge in every" 
        t_next "battle.@" 
};
static const struct DexEntry MachopPokedexEntry = {
    .category = "SUPERPOWER@", // species name
    .height = 207, .weight = 430, // height, weight
    .description = "It trains by"  
        t_next "lifting rocks in" 
        t_next "the mountains. It" 
        t_page "can even pick up a" 
        t_next "GRAVELER with" 
        t_next "ease.@" 
};
static const struct DexEntry MachokePokedexEntry = {
    .category = "SUPERPOWER@", // species name
    .height = 411, .weight = 1550, // height, weight
    .description = "This tough #MON"  
        t_next "always stays in" 
        t_next "the zone. Its" 
        t_page "muscles become" 
        t_next "thicker after" 
        t_next "every battle.@" 
};
static const struct DexEntry MachampPokedexEntry = {
    .category = "SUPERPOWER@", // species name
    .height = 503, .weight = 2870, // height, weight
    .description = "With four arms"  
        t_next "that react more" 
        t_next "quickly than it" 
        t_page "can think, it can" 
        t_next "execute many" 
        t_next "punches at once.@" 
};
static const struct DexEntry BellsproutPokedexEntry = {
    .category = "FLOWER@", // species name
    .height = 204, .weight = 90, // height, weight
    .description = "If it notices"  
        t_next "anything that" 
        t_next "moves, it" 
        t_page "immediately flings" 
        t_next "its vine at the" 
        t_next "object.@" 
};
static const struct DexEntry WeepinbellPokedexEntry = {
    .category = "FLYCATCHER@", // species name
    .height = 303, .weight = 140, // height, weight
    .description = "When it's hungry,"  
        t_next "it swings its" 
        t_next "razor-sharp" 
        t_page "leaves, slicing up" 
        t_next "any unlucky object" 
        t_next "nearby for food.@" 
};
static const struct DexEntry VictreebelPokedexEntry = {
    .category = "FLYCATCHER@", // species name
    .height = 507, .weight = 340, // height, weight
    .description = "Once ingested into"  
        t_next "this #MON's" 
        t_next "body, even the" 
        t_page "hardest object" 
        t_next "will melt into" 
        t_next "nothing.@" 
};
static const struct DexEntry TentacoolPokedexEntry = {
    .category = "JELLYFISH@", // species name
    .height = 211, .weight = 1000, // height, weight
    .description = "As it floats along"  
        t_next "on the waves, it" 
        t_next "uses its toxic" 
        t_page "feelers to stab" 
        t_next "anything it" 
        t_next "touches.@" 
};
static const struct DexEntry TentacruelPokedexEntry = {
    .category = "JELLYFISH@", // species name
    .height = 503, .weight = 1210, // height, weight
    .description = "When its 80 feel-"  
        t_next "ers absorb water," 
        t_next "it stretches to" 
        t_page "become like a net" 
        t_next "to entangle its" 
        t_next "prey.@" 
};
static const struct DexEntry GeodudePokedexEntry = {
    .category = "ROCK@", // species name
    .height = 104, .weight = 440, // height, weight
    .description = "Proud of their"  
        t_next "sturdy bodies," 
        t_next "they bash against" 
        t_page "each other in a" 
        t_next "contest to prove" 
        t_next "whose is harder.@" 
};
static const struct DexEntry GravelerPokedexEntry = {
    .category = "ROCK@", // species name
    .height = 303, .weight = 2320, // height, weight
    .description = "It travels by rol-"  
        t_next "ling on mountain" 
        t_next "paths. If it gains" 
        t_page "too much speed, it" 
        t_next "stops by running" 
        t_next "into huge rocks.@" 
};
static const struct DexEntry GolemPokedexEntry = {
    .category = "MEGATON@", // species name
    .height = 407, .weight = 6620, // height, weight
    .description = "Its rock-like body"  
        t_next "is so durable," 
        t_next "even high-powered" 
        t_page "dynamite blasts" 
        t_next "fail to scratch" 
        t_next "its rugged hide.@" 
};
static const struct DexEntry PonytaPokedexEntry = {
    .category = "FIRE HORSE@", // species name
    .height = 303, .weight = 660, // height, weight
    .description = "Training by"  
        t_next "jumping over grass" 
        t_next "that grows longer" 
        t_page "every day has made" 
        t_next "it a world-class" 
        t_next "jumper.@" 
};
static const struct DexEntry RapidashPokedexEntry = {
    .category = "FIRE HORSE@", // species name
    .height = 507, .weight = 2090, // height, weight
    .description = "It just loves to"  
        t_next "gallop. The faster" 
        t_next "it goes, the long-" 
        t_page "er the swaying" 
        t_next "flames of its mane" 
        t_next "will become.@" 
};
static const struct DexEntry SlowpokePokedexEntry = {
    .category = "DOPEY@", // species name
    .height = 311, .weight = 790, // height, weight
    .description = "It is always so"  
        t_next "absent-minded that" 
        t_next "it won't react," 
        t_page "even if its" 
        t_next "flavorful tail is" 
        t_next "bitten.@" 
};
static const struct DexEntry SlowbroPokedexEntry = {
    .category = "HERMITCRAB@", // species name
    .height = 503, .weight = 1730, // height, weight
    .description = "An attached"  
        t_next "SHELLDER won't let" 
        t_next "go because of the" 
        t_page "tasty flavor that" 
        t_next "oozes out of its" 
        t_next "tail.@" 
};
static const struct DexEntry MagnemitePokedexEntry = {
    .category = "MAGNET@", // species name
    .height = 100, .weight = 130, // height, weight
    .description = "The electricity"  
        t_next "emitted by the" 
        t_next "units on each side" 
        t_page "of its body cause" 
        t_next "it to become a" 
        t_next "strong magnet.@" 
};
static const struct DexEntry MagnetonPokedexEntry = {
    .category = "MAGNET@", // species name
    .height = 303, .weight = 1320, // height, weight
    .description = "When many"  
        t_next "MAGNETON gather" 
        t_next "together, the" 
        t_page "resulting magnetic" 
        t_next "storm disrupts" 
        t_next "radio waves.@" 
};
static const struct DexEntry FarfetchDPokedexEntry = {
    .category = "WILD DUCK@", // species name
    .height = 207, .weight = 330, // height, weight
    .description = "In order to pre-"  
        t_next "vent their" 
        t_next "extinction, more" 
        t_page "people have made" 
        t_next "an effort to breed" 
        t_next "these #MON.@" 
};
static const struct DexEntry DoduoPokedexEntry = {
    .category = "TWIN BIRD@", // species name
    .height = 407, .weight = 860, // height, weight
    .description = "It lives on a"  
        t_next "grassy plain where" 
        t_next "it can see a long" 
        t_page "way. If it sees an" 
        t_next "enemy, it runs" 
        t_next "away at 60 mph.@" 
};
static const struct DexEntry DodrioPokedexEntry = {
    .category = "TRIPLEBIRD@", // species name
    .height = 511, .weight = 1880, // height, weight
    .description = "An enemy that"  
        t_next "takes its eyes off" 
        t_next "any of the three" 
        t_page "heads--even for a" 
        t_next "second--will get" 
        t_next "pecked severely.@" 
};
static const struct DexEntry SeelPokedexEntry = {
    .category = "SEA LION@", // species name
    .height = 307, .weight = 1980, // height, weight
    .description = "The light blue fur"  
        t_next "that covers it" 
        t_next "keeps it protected" 
        t_page "against the cold." 
        t_next "It loves iceberg-" 
        t_next "filled oceans.@" 
};
static const struct DexEntry DewgongPokedexEntry = {
    .category = "SEA LION@", // species name
    .height = 507, .weight = 2650, // height, weight
    .description = "It sleeps under"  
        t_next "shallow ocean" 
        t_next "waters during the" 
        t_page "day, then looks" 
        t_next "for food at night" 
        t_next "when it's cold.@" 
};
static const struct DexEntry GrimerPokedexEntry = {
    .category = "SLUDGE@", // species name
    .height = 211, .weight = 660, // height, weight
    .description = "When two of these"  
        t_next "#MON's bodies" 
        t_next "are combined" 
        t_page "together, new" 
        t_next "poisons are" 
        t_next "created.@" 
};
static const struct DexEntry MukPokedexEntry = {
    .category = "SLUDGE@", // species name
    .height = 311, .weight = 660, // height, weight
    .description = "As it moves, a"  
        t_next "very strong poison" 
        t_next "leaks from it," 
        t_page "making the ground" 
        t_next "there barren for" 
        t_next "three years.@" 
};
static const struct DexEntry ShellderPokedexEntry = {
    .category = "BIVALVE@", // species name
    .height = 100, .weight = 90, // height, weight
    .description = "Clamping on to an"  
        t_next "opponent reveals" 
        t_next "its vulnerable" 
        t_page "parts, so it uses" 
        t_next "this move only as" 
        t_next "a last resort.@" 
};
static const struct DexEntry CloysterPokedexEntry = {
    .category = "BIVALVE@", // species name
    .height = 411, .weight = 2920, // height, weight
    .description = "Even a missile"  
        t_next "can't break the" 
        t_next "spikes it uses to" 
        t_page "stab opponents." 
        t_next "They're even hard-" 
        t_next "er than its shell.@" 
};
static const struct DexEntry GastlyPokedexEntry = {
    .category = "GAS@", // species name
    .height = 403, .weight = 2, // height, weight
    .description = "It wraps its op-"  
        t_next "ponent in its gas-" 
        t_next "like body, slowly" 
        t_page "weakening its prey" 
        t_next "by poisoning it" 
        t_next "through the skin.@" 
};
static const struct DexEntry HaunterPokedexEntry = {
    .category = "GAS@", // species name
    .height = 503, .weight = 2, // height, weight
    .description = "It hides in the"  
        t_next "dark, planning to" 
        t_next "take the life of" 
        t_page "the next living" 
        t_next "thing that wanders" 
        t_next "close by.@" 
};
static const struct DexEntry GengarPokedexEntry = {
    .category = "SHADOW@", // species name
    .height = 411, .weight = 890, // height, weight
    .description = "Hiding in people's"  
        t_next "shadows at night," 
        t_next "it absorbs their" 
        t_page "heat. The chill it" 
        t_next "causes makes the" 
        t_next "victims shake.@" 
};
static const struct DexEntry OnixPokedexEntry = {
    .category = "ROCK SNAKE@", // species name
    .height = 2810, .weight = 4630, // height, weight
    .description = "As it digs through"  
        t_next "the ground, it" 
        t_next "absorbs many hard" 
        t_page "objects. This is" 
        t_next "what makes its" 
        t_next "body so solid.@" 
};
static const struct DexEntry DrowzeePokedexEntry = {
    .category = "HYPNOSIS@", // species name
    .height = 303, .weight = 710, // height, weight
    .description = "When it twitches"  
        t_next "its nose, it can" 
        t_next "tell where someone" 
        t_page "is sleeping and" 
        t_next "what that person" 
        t_next "is dreaming about.@" 
};
static const struct DexEntry HypnoPokedexEntry = {
    .category = "HYPNOSIS@", // species name
    .height = 503, .weight = 1670, // height, weight
    .description = "The longer it"  
        t_next "swings its" 
        t_next "pendulum, the" 
        t_page "longer the effects" 
        t_next "of its hypnosis" 
        t_next "last.@" 
};
static const struct DexEntry KrabbyPokedexEntry = {
    .category = "RIVER CRAB@", // species name
    .height = 104, .weight = 140, // height, weight
    .description = "If it is unable"  
        t_next "to find food, it" 
        t_next "will absorb" 
        t_page "nutrients by" 
        t_next "swallowing a" 
        t_next "mouthful of sand.@" 
};
static const struct DexEntry KinglerPokedexEntry = {
    .category = "PINCER@", // species name
    .height = 403, .weight = 1320, // height, weight
    .description = "Its oversized claw"  
        t_next "is very powerful," 
        t_next "but when it's not" 
        t_page "in battle, the" 
        t_next "claw just gets in" 
        t_next "the way.@" 
};
static const struct DexEntry VoltorbPokedexEntry = {
    .category = "BALL@", // species name
    .height = 108, .weight = 230, // height, weight
    .description = "During the study"  
        t_next "of this #MON," 
        t_next "it was discovered" 
        t_page "that its compo-" 
        t_next "nents are not" 
        t_next "found in nature.@" 
};
static const struct DexEntry ElectrodePokedexEntry = {
    .category = "BALL@", // species name
    .height = 311, .weight = 1470, // height, weight
    .description = "The more energy it"  
        t_next "charges up, the" 
        t_next "faster it gets." 
        t_page "But this also" 
        t_next "makes it more" 
        t_next "likely to explode.@" 
};
static const struct DexEntry ExeggcutePokedexEntry = {
    .category = "EGG@", // species name
    .height = 104, .weight = 60, // height, weight
    .description = "If even one is"  
        t_next "separated from the" 
        t_next "group, the energy" 
        t_page "bond between the" 
        t_next "six will make them" 
        t_next "rejoin instantly.@" 
};
static const struct DexEntry ExeggutorPokedexEntry = {
    .category = "COCONUT@", // species name
    .height = 607, .weight = 2650, // height, weight
    .description = "Living in a good"  
        t_next "environment makes" 
        t_next "it grow lots of" 
        t_page "heads. A head that" 
        t_next "drops off becomes" 
        t_next "an EXEGGCUTE.@" 
};
static const struct DexEntry CubonePokedexEntry = {
    .category = "LONELY@", // species name
    .height = 104, .weight = 140, // height, weight
    .description = "It lost its mother"  
        t_next "after its birth." 
        t_next "It wears its" 
        t_page "mother's skull," 
        t_next "never revealing" 
        t_next "its true face.@" 
};
static const struct DexEntry MarowakPokedexEntry = {
    .category = "BONEKEEPER@", // species name
    .height = 303, .weight = 990, // height, weight
    .description = "Somewhere in the"  
        t_next "world is a ceme-" 
        t_next "tery just for" 
        t_page "MAROWAK. It gets" 
        t_next "its bones from" 
        t_next "those graves.@" 
};
static const struct DexEntry HitmonleePokedexEntry = {
    .category = "KICKING@", // species name
    .height = 411, .weight = 1100, // height, weight
    .description = "It is also called"  
        t_next "the Kick Master." 
        t_next "It uses its" 
        t_page "elastic legs to" 
        t_next "execute every" 
        t_next "known kick.@" 
};
static const struct DexEntry HitmonchanPokedexEntry = {
    .category = "PUNCHING@", // species name
    .height = 407, .weight = 1110, // height, weight
    .description = "To increase the"  
        t_next "strength of all" 
        t_next "its punch moves," 
        t_page "it spins its arms" 
        t_next "just before making" 
        t_next "contact.@" 
};
static const struct DexEntry LickitungPokedexEntry = {
    .category = "LICKING@", // species name
    .height = 311, .weight = 1440, // height, weight
    .description = "It has a tongue"  
        t_next "that is over 6'6''" 
        t_next "long. It uses this" 
        t_page "long tongue to" 
        t_next "lick its body" 
        t_next "clean.@" 
};
static const struct DexEntry KoffingPokedexEntry = {
    .category = "POISON GAS@", // species name
    .height = 200, .weight = 20, // height, weight
    .description = "If one gets close"  
        t_next "enough to it when" 
        t_next "it expels poison-" 
        t_page "ous gas, the gas" 
        t_next "swirling inside it" 
        t_next "can be seen.@" 
};
static const struct DexEntry WeezingPokedexEntry = {
    .category = "POISON GAS@", // species name
    .height = 311, .weight = 210, // height, weight
    .description = "When it inhales"  
        t_next "poisonous gases" 
        t_next "from garbage, its" 
        t_page "body expands, and" 
        t_next "its insides smell" 
        t_next "much worse.@" 
};
static const struct DexEntry RhyhornPokedexEntry = {
    .category = "SPIKES@", // species name
    .height = 303, .weight = 2540, // height, weight
    .description = "It can remember"  
        t_next "only one thing at" 
        t_next "a time. Once it" 
        t_page "starts rushing, it" 
        t_next "forgets why it" 
        t_next "started.@" 
};
static const struct DexEntry RhydonPokedexEntry = {
    .category = "DRILL@", // species name
    .height = 603, .weight = 2650, // height, weight
    .description = "By lightly spin-"  
        t_next "ning its drill-" 
        t_next "like horn, it can" 
        t_page "easily shatter" 
        t_next "even a diamond in" 
        t_next "the rough.@" 
};
static const struct DexEntry ChanseyPokedexEntry = {
    .category = "EGG@", // species name
    .height = 307, .weight = 760, // height, weight
    .description = "People try to"  
        t_next "catch it for its" 
        t_next "extremely" 
        t_page "nutritious eggs," 
        t_next "but it rarely can" 
        t_next "be found.@" 
};
static const struct DexEntry TangelaPokedexEntry = {
    .category = "VINE@", // species name
    .height = 303, .weight = 770, // height, weight
    .description = "During battle, it"  
        t_next "constantly moves" 
        t_next "the vines that" 
        t_page "cover its body in" 
        t_next "order to annoy its" 
        t_next "opponent.@" 
};
static const struct DexEntry KangaskhanPokedexEntry = {
    .category = "PARENT@", // species name
    .height = 703, .weight = 1760, // height, weight
    .description = "To avoid"  
        t_next "crushing the" 
        t_next "baby it carries in" 
        t_page "its pouch, it" 
        t_next "always sleeps" 
        t_next "standing up.@" 
};
static const struct DexEntry HorseaPokedexEntry = {
    .category = "DRAGON@", // species name
    .height = 104, .weight = 180, // height, weight
    .description = "When they're in a"  
        t_next "safe location," 
        t_next "they can be seen" 
        t_page "playfully tangling" 
        t_next "their tails" 
        t_next "together.@" 
};
static const struct DexEntry SeadraPokedexEntry = {
    .category = "DRAGON@", // species name
    .height = 311, .weight = 550, // height, weight
    .description = "The male raises"  
        t_next "the young. If it" 
        t_next "is approached, it" 
        t_page "uses its toxic" 
        t_next "spikes to fend off" 
        t_next "the intruder.@" 
};
static const struct DexEntry GoldeenPokedexEntry = {
    .category = "GOLDFISH@", // species name
    .height = 200, .weight = 330, // height, weight
    .description = "During spawning"  
        t_next "season, they swim" 
        t_next "gracefully in the" 
        t_page "water, searching" 
        t_next "for their perfect" 
        t_next "mate.@" 
};
static const struct DexEntry SeakingPokedexEntry = {
    .category = "GOLDFISH@", // species name
    .height = 403, .weight = 860, // height, weight
    .description = "When autumn comes,"  
        t_next "the males patrol" 
        t_next "the area around" 
        t_page "their nests in" 
        t_next "order to protect" 
        t_next "their offspring.@" 
};
static const struct DexEntry StaryuPokedexEntry = {
    .category = "STARSHAPE@", // species name
    .height = 207, .weight = 760, // height, weight
    .description = "When the stars"  
        t_next "twinkle at night," 
        t_next "it floats up from" 
        t_page "the sea floor, and" 
        t_next "its body's center" 
        t_next "core flickers.@" 
};
static const struct DexEntry StarmiePokedexEntry = {
    .category = "MYSTERIOUS@", // species name
    .height = 307, .weight = 1760, // height, weight
    .description = "It is said that it"  
        t_next "uses the seven-" 
        t_next "colored core of" 
        t_page "its body to send" 
        t_next "electric waves" 
        t_next "into outer space.@" 
};
static const struct DexEntry MrMimePokedexEntry = {
    .category = "BARRIER@", // species name
    .height = 403, .weight = 1200, // height, weight
    .description = "It uses the"  
        t_next "mysterious" 
        t_next "power it has in" 
        t_page "its fingers to" 
        t_next "solidify air into" 
        t_next "an invisible wall.@" 
};
static const struct DexEntry ScytherPokedexEntry = {
    .category = "MANTIS@", // species name
    .height = 411, .weight = 1230, // height, weight
    .description = "It's very proud of"  
        t_next "its speed. It" 
        t_next "moves so fast that" 
        t_page "its opponent does" 
        t_next "not even know what" 
        t_next "knocked it down.@" 
};
static const struct DexEntry JynxPokedexEntry = {
    .category = "HUMANSHAPE@", // species name
    .height = 407, .weight = 900, // height, weight
    .description = "It has several"  
        t_next "different cry pat-" 
        t_next "terns, each of" 
        t_page "which seems to" 
        t_next "have its own" 
        t_next "meaning.@" 
};
static const struct DexEntry ElectabuzzPokedexEntry = {
    .category = "ELECTRIC@", // species name
    .height = 307, .weight = 660, // height, weight
    .description = "When two"  
        t_next "ELECTABUZZ touch," 
        t_next "they control the" 
        t_page "electric currents" 
        t_next "to communicate" 
        t_next "their feelings.@" 
};
static const struct DexEntry MagmarPokedexEntry = {
    .category = "SPITFIRE@", // species name
    .height = 403, .weight = 980, // height, weight
    .description = "It moves more"  
        t_next "frequently in hot" 
        t_next "areas. It can heal" 
        t_page "itself by dipping" 
        t_next "its wound into" 
        t_next "lava.@" 
};
static const struct DexEntry PinsirPokedexEntry = {
    .category = "STAGBEETLE@", // species name
    .height = 411, .weight = 1210, // height, weight
    .description = "When the tempera-"  
        t_next "ture drops at" 
        t_next "night, it sleeps" 
        t_page "on treetops or" 
        t_next "among roots where" 
        t_next "it is well hidden.@" 
};
static const struct DexEntry TaurosPokedexEntry = {
    .category = "WILD BULL@", // species name
    .height = 407, .weight = 1950, // height, weight
    .description = "These violent"  
        t_next "#MON fight" 
        t_next "with other mem-" 
        t_page "bers of their herd" 
        t_next "in order to prove" 
        t_next "their strength.@" 
};
static const struct DexEntry MagikarpPokedexEntry = {
    .category = "FISH@", // species name
    .height = 211, .weight = 220, // height, weight
    .description = "This weak and"  
        t_next "pathetic #MON" 
        t_next "gets easily pushed" 
        t_page "along rivers when" 
        t_next "there are strong" 
        t_next "currents.@" 
};
static const struct DexEntry GyaradosPokedexEntry = {
    .category = "ATROCIOUS@", // species name
    .height = 2104, .weight = 5180, // height, weight
    .description = "It appears when-"  
        t_next "ever there is" 
        t_next "world conflict," 
        t_page "burning down any" 
        t_next "place it travels" 
        t_next "through.@" 
};
static const struct DexEntry LaprasPokedexEntry = {
    .category = "TRANSPORT@", // species name
    .height = 802, .weight = 4850, // height, weight
    .description = "This gentle"  
        t_next "#MON loves to" 
        t_next "give people rides" 
        t_page "and provides a ve-" 
        t_next "ry comfortable way" 
        t_next "to get around.@" 
};
static const struct DexEntry DittoPokedexEntry = {
    .category = "TRANSFORM@", // species name
    .height = 100, .weight = 90, // height, weight
    .description = "When it encount-"  
        t_next "ers another DITTO," 
        t_next "it will move" 
        t_page "faster than normal" 
        t_next "to duplicate that" 
        t_next "opponent exactly.@" 
};
static const struct DexEntry EeveePokedexEntry = {
    .category = "EVOLUTION@", // species name
    .height = 100, .weight = 140, // height, weight
    .description = "Its ability to"  
        t_next "evolve into many" 
        t_next "forms allows it to" 
        t_page "adapt smoothly" 
        t_next "and perfectly to" 
        t_next "any environment.@" 
};
static const struct DexEntry VaporeonPokedexEntry = {
    .category = "BUBBLE JET@", // species name
    .height = 303, .weight = 640, // height, weight
    .description = "As it uses the"  
        t_next "fins on the tip" 
        t_next "of its tail to" 
        t_page "swim, it blends" 
        t_next "with the water" 
        t_next "perfectly.@" 
};
static const struct DexEntry JolteonPokedexEntry = {
    .category = "LIGHTNING@", // species name
    .height = 207, .weight = 540, // height, weight
    .description = "The negatively"  
        t_next "charged ions" 
        t_next "generated in its" 
        t_page "fur create a" 
        t_next "constant sparking" 
        t_next "noise.@" 
};
static const struct DexEntry FlareonPokedexEntry = {
    .category = "FLAME@", // species name
    .height = 211, .weight = 550, // height, weight
    .description = "Once it has stored"  
        t_next "up enough heat," 
        t_next "this #MON's" 
        t_page "body temperature" 
        t_next "can reach up to" 
        t_next "1700 degrees.@" 
};
static const struct DexEntry PorygonPokedexEntry = {
    .category = "VIRTUAL@", // species name
    .height = 207, .weight = 800, // height, weight
    .description = "An artificial"  
        t_next "#MON created" 
        t_next "due to extensive" 
        t_page "research, it can" 
        t_next "perform only what" 
        t_next "is in its program.@" 
};
static const struct DexEntry OmanytePokedexEntry = {
    .category = "SPIRAL@", // species name
    .height = 104, .weight = 170, // height, weight
    .description = "In prehistoric"  
        t_next "times, it swam on" 
        t_next "the sea floor," 
        t_page "eating plankton." 
        t_next "Its fossils are" 
        t_next "sometimes found.@" 
};
static const struct DexEntry OmastarPokedexEntry = {
    .category = "SPIRAL@", // species name
    .height = 303, .weight = 770, // height, weight
    .description = "Its heavy shell"  
        t_next "allowed it to" 
        t_next "reach only nearby" 
        t_page "food. This could" 
        t_next "be the reason it" 
        t_next "is extinct.@" 
};
static const struct DexEntry KabutoPokedexEntry = {
    .category = "SHELLFISH@", // species name
    .height = 108, .weight = 250, // height, weight
    .description = "Three hundred"  
        t_next "million years ago," 
        t_next "it hid on the sea" 
        t_page "floor. It also has" 
        t_next "eyes on its back" 
        t_next "that glow.@" 
};
static const struct DexEntry KabutopsPokedexEntry = {
    .category = "SHELLFISH@", // species name
    .height = 403, .weight = 890, // height, weight
    .description = "It was able to"  
        t_next "swim quickly thro-" 
        t_next "ugh the water by" 
        t_page "compactly folding" 
        t_next "up its razor-sharp" 
        t_next "sickles.@" 
};
static const struct DexEntry AerodactylPokedexEntry = {
    .category = "FOSSIL@", // species name
    .height = 511, .weight = 1300, // height, weight
    .description = "In prehistoric"  
        t_next "times, this" 
        t_next "#MON flew" 
        t_page "freely and" 
        t_next "fearlessly through" 
        t_next "the skies.@" 
};
static const struct DexEntry SnorlaxPokedexEntry = {
    .category = "SLEEPING@", // species name
    .height = 611, .weight = 10140, // height, weight
    .description = "This #MON's"  
        t_next "stomach is so" 
        t_next "strong, even" 
        t_page "eating moldy or" 
        t_next "rotten food will" 
        t_next "not affect it.@" 
};
static const struct DexEntry ArticunoPokedexEntry = {
    .category = "FREEZE@", // species name
    .height = 507, .weight = 1220, // height, weight
    .description = "Legendary bird"  
        t_next "#MON. As it" 
        t_next "flies through the" 
        t_page "sky, it cools the" 
        t_next "air, causing snow" 
        t_next "to fall.@" 
};
static const struct DexEntry ZapdosPokedexEntry = {
    .category = "ELECTRIC@", // species name
    .height = 503, .weight = 1160, // height, weight
    .description = "Legendary bird"  
        t_next "#MON. They say" 
        t_next "lightning caused" 
        t_page "by the flapping of" 
        t_next "its wings causes" 
        t_next "summer storms.@" 
};
static const struct DexEntry MoltresPokedexEntry = {
    .category = "FLAME@", // species name
    .height = 607, .weight = 1320, // height, weight
    .description = "Legendary bird"  
        t_next "#MON. It is" 
        t_next "said to migrate" 
        t_page "from the south" 
        t_next "along with the" 
        t_next "spring.@" 
};
static const struct DexEntry DratiniPokedexEntry = {
    .category = "DRAGON@", // species name
    .height = 511, .weight = 70, // height, weight
    .description = "It sheds many lay-"  
        t_next "ers of skin as it" 
        t_next "grows larger. Dur-" 
        t_page "ing this process," 
        t_next "it is protected by" 
        t_next "a rapid waterfall.@" 
};
static const struct DexEntry DragonairPokedexEntry = {
    .category = "DRAGON@", // species name
    .height = 1301, .weight = 360, // height, weight
    .description = "It is called the"  
        t_next "divine #MON." 
        t_next "When its entire" 
        t_page "body brightens" 
        t_next "slightly, the" 
        t_next "weather changes.@" 
};
static const struct DexEntry DragonitePokedexEntry = {
    .category = "DRAGON@", // species name
    .height = 703, .weight = 4630, // height, weight
    .description = "It is said that"  
        t_next "somewhere in the" 
        t_next "ocean lies an" 
        t_page "island where these" 
        t_next "gather. Only they" 
        t_next "live there.@" 
};
static const struct DexEntry MewtwoPokedexEntry = {
    .category = "GENETIC@", // species name
    .height = 607, .weight = 2690, // height, weight
    .description = "Said to rest qui-"  
        t_next "etly in an" 
        t_next "undiscovered cave," 
        t_page "this #MON was" 
        t_next "created solely for" 
        t_next "battling.@" 
};
static const struct DexEntry MewPokedexEntry = {
    .category = "NEW SPECIE@", // species name
    .height = 104, .weight = 90, // height, weight
    .description = "Because it can"  
        t_next "learn any move," 
        t_next "some people began" 
        t_page "research to see if" 
        t_next "it is the ancestor" 
        t_next "of all #MON.@" 
};
static const struct DexEntry ChikoritaPokedexEntry = {
    .category = "LEAF@", // species name
    .height = 211, .weight = 140, // height, weight
    .description = "It loves to bask"  
        t_next "in the sunlight." 
        t_next "It uses the leaf" 
        t_page "on its head to" 
        t_next "seek out warm" 
        t_next "places.@" 
};
static const struct DexEntry BayleefPokedexEntry = {
    .category = "LEAF@", // species name
    .height = 311, .weight = 350, // height, weight
    .description = "The scent that"  
        t_next "wafts from the" 
        t_next "leaves on its neck" 
        t_page "causes anyone who" 
        t_next "smells it to" 
        t_next "become energetic.@" 
};
static const struct DexEntry MeganiumPokedexEntry = {
    .category = "HERB@", // species name
    .height = 511, .weight = 2220, // height, weight
    .description = "Anyone who stands"  
        t_next "beside it becomes" 
        t_next "refreshed, just as" 
        t_page "if they were" 
        t_next "relaxing in a" 
        t_next "sunny forest.@" 
};
static const struct DexEntry CyndaquilPokedexEntry = {
    .category = "FIRE MOUSE@", // species name
    .height = 108, .weight = 170, // height, weight
    .description = "The fire that"  
        t_next "spouts from its" 
        t_next "back burns hottest" 
        t_page "when it is angry." 
        t_next "The flaring flames" 
        t_next "intimidate foes.@" 
};
static const struct DexEntry QuilavaPokedexEntry = {
    .category = "VOLCANO@", // species name
    .height = 211, .weight = 420, // height, weight
    .description = "Before battle, it"  
        t_next "turns its back on" 
        t_next "its opponent to" 
        t_page "demonstrate how" 
        t_next "ferociously its" 
        t_next "fire blazes.@" 
};
static const struct DexEntry TyphlosionPokedexEntry = {
    .category = "VOLCANO@", // species name
    .height = 507, .weight = 1750, // height, weight
    .description = "When heat from its"  
        t_next "body causes the" 
        t_next "air around it to" 
        t_page "shimmer, this is a" 
        t_next "sign that it is" 
        t_next "ready to battle.@" 
};
static const struct DexEntry TotodilePokedexEntry = {
    .category = "BIG JAW@", // species name
    .height = 200, .weight = 210, // height, weight
    .description = "This rough critter"  
        t_next "chomps at any" 
        t_next "moving object it" 
        t_page "sees. Turning your" 
        t_next "back on it is not" 
        t_next "recommended.@" 
};
static const struct DexEntry CroconawPokedexEntry = {
    .category = "BIG JAW@", // species name
    .height = 307, .weight = 550, // height, weight
    .description = "The tips of its"  
        t_next "fangs are slanted" 
        t_next "backward. Once" 
        t_page "those fangs clamp" 
        t_next "down, the prey has" 
        t_next "no hope of escape.@" 
};
static const struct DexEntry FeraligatrPokedexEntry = {
    .category = "BIG JAW@", // species name
    .height = 707, .weight = 1960, // height, weight
    .description = "Although it has a"  
        t_next "massive body, its" 
        t_next "powerful hind legs" 
        t_page "enable it to move" 
        t_next "quickly, even on" 
        t_next "the ground.@" 
};
static const struct DexEntry SentretPokedexEntry = {
    .category = "SCOUT@", // species name
    .height = 207, .weight = 130, // height, weight
    .description = "When acting as a"  
        t_next "lookout, it warns" 
        t_next "others of danger" 
        t_page "by screeching and" 
        t_next "hitting the ground" 
        t_next "with its tail.@" 
};
static const struct DexEntry FurretPokedexEntry = {
    .category = "LONG BODY@", // species name
    .height = 511, .weight = 720, // height, weight
    .description = "It lives in narrow"  
        t_next "burrows that fit" 
        t_next "its slim body. The" 
        t_page "deeper the nests" 
        t_next "go, the more maze-" 
        t_next "like they become.@" 
};
static const struct DexEntry HoothootPokedexEntry = {
    .category = "OWL@", // species name
    .height = 204, .weight = 470, // height, weight
    .description = "It begins to hoot"  
        t_next "at the same time" 
        t_next "every day. Some" 
        t_page "trainers use them" 
        t_next "in place of" 
        t_next "clocks.@" 
};
static const struct DexEntry NoctowlPokedexEntry = {
    .category = "OWL@", // species name
    .height = 503, .weight = 900, // height, weight
    .description = "Its extremely soft"  
        t_next "feathers make no" 
        t_next "sound in flight." 
        t_page "It silently sneaks" 
        t_next "up on prey without" 
        t_next "being detected.@" 
};
static const struct DexEntry LedybaPokedexEntry = {
    .category = "FIVE STAR@", // species name
    .height = 303, .weight = 240, // height, weight
    .description = "It is timid and"  
        t_next "clusters together" 
        t_next "with others. The" 
        t_page "fluid secreted by" 
        t_next "its feet indicates" 
        t_next "its location.@" 
};
static const struct DexEntry LedianPokedexEntry = {
    .category = "FIVE STAR@", // species name
    .height = 407, .weight = 780, // height, weight
    .description = "In the daytime"  
        t_next "when it gets warm," 
        t_next "it curls up inside" 
        t_page "a big leaf and" 
        t_next "drifts off into" 
        t_next "a deep slumber.@" 
};
static const struct DexEntry SpinarakPokedexEntry = {
    .category = "STRINGSPIT@", // species name
    .height = 108, .weight = 190, // height, weight
    .description = "If prey becomes"  
        t_next "ensnared in its" 
        t_next "nest of spun" 
        t_page "string, it waits" 
        t_next "motionlessly until" 
        t_next "it becomes dark.@" 
};
static const struct DexEntry AriadosPokedexEntry = {
    .category = "LONG LEG@", // species name
    .height = 307, .weight = 740, // height, weight
    .description = "Rather than mak-"  
        t_next "ing a nest in one" 
        t_next "specific spot, it" 
        t_page "wanders in search" 
        t_next "of food after" 
        t_next "darkness falls.@" 
};
static const struct DexEntry CrobatPokedexEntry = {
    .category = "BAT@", // species name
    .height = 511, .weight = 1650, // height, weight
    .description = "As a result of its"  
        t_next "pursuit of faster," 
        t_next "yet more silent" 
        t_page "flight, a new set" 
        t_next "of wings grew on" 
        t_next "its hind legs.@" 
};
static const struct DexEntry ChinchouPokedexEntry = {
    .category = "ANGLER@", // species name
    .height = 108, .weight = 260, // height, weight
    .description = "Its antennae, whi-"  
        t_next "ch evolved from a" 
        t_next "fin, have both po-" 
        t_page "sitive and neg-" 
        t_next "ative charges flo-" 
        t_next "wing through them.@" 
};
static const struct DexEntry LanturnPokedexEntry = {
    .category = "LIGHT@", // species name
    .height = 311, .weight = 500, // height, weight
    .description = "This #MON uses"  
        t_next "the bright part of" 
        t_next "its body, which" 
        t_page "changed from a" 
        t_next "dorsal fin, to" 
        t_next "lure prey.@" 
};
static const struct DexEntry PichuPokedexEntry = {
    .category = "TINY MOUSE@", // species name
    .height = 100, .weight = 40, // height, weight
    .description = "It is unskilled at"  
        t_next "storing electric" 
        t_next "power. Any kind of" 
        t_page "shock causes it to" 
        t_next "discharge energy" 
        t_next "spontaneously.@" 
};
static const struct DexEntry CleffaPokedexEntry = {
    .category = "STARSHAPE@", // species name
    .height = 100, .weight = 70, // height, weight
    .description = "If the impact site"  
        t_next "of a meteorite is" 
        t_next "found, this" 
        t_page "#MON is certain" 
        t_next "to be within the" 
        t_next "immediate area.@" 
};
static const struct DexEntry IgglybuffPokedexEntry = {
    .category = "BALLOON@", // species name
    .height = 100, .weight = 20, // height, weight
    .description = "Instead of walking"  
        t_next "with its short" 
        t_next "legs, it moves" 
        t_page "around by bouncing" 
        t_next "on its soft," 
        t_next "tender body.@" 
};
static const struct DexEntry TogepiPokedexEntry = {
    .category = "SPIKE BALL@", // species name
    .height = 100, .weight = 30, // height, weight
    .description = "It is considered"  
        t_next "to be a symbol of" 
        t_next "good luck. Its" 
        t_page "shell is said to" 
        t_next "be filled with" 
        t_next "happiness.@" 
};
static const struct DexEntry TogeticPokedexEntry = {
    .category = "HAPPINESS@", // species name
    .height = 200, .weight = 70, // height, weight
    .description = "Although it does"  
        t_next "not flap its wings" 
        t_next "very much, it can" 
        t_page "stay up in the air" 
        t_next "as it tags along" 
        t_next "after its trainer.@" 
};
static const struct DexEntry NatuPokedexEntry = {
    .category = "LITTLE BIRD@", // species name
    .height = 8, .weight = 40, // height, weight
    .description = "It is extremely"  
        t_next "good at climbing" 
        t_next "tree trunks and" 
        t_page "likes to eat the" 
        t_next "new sprouts on" 
        t_next "the trees.@" 
};
static const struct DexEntry XatuPokedexEntry = {
    .category = "MYSTIC@", // species name
    .height = 411, .weight = 330, // height, weight
    .description = "Once it begins to"  
        t_next "meditate at sun-" 
        t_next "rise, the entire" 
        t_page "day will pass" 
        t_next "before it will" 
        t_next "move again.@" 
};
static const struct DexEntry MareepPokedexEntry = {
    .category = "WOOL@", // species name
    .height = 200, .weight = 170, // height, weight
    .description = "It stores lots of"  
        t_next "air in its soft" 
        t_next "fur, allowing it" 
        t_page "to stay cool in" 
        t_next "summer and warm" 
        t_next "in winter.@" 
};
static const struct DexEntry FlaaffyPokedexEntry = {
    .category = "WOOL@", // species name
    .height = 207, .weight = 290, // height, weight
    .description = "Because of its"  
        t_next "rubbery, electric-" 
        t_next "ity-resistant" 
        t_page "skin, it can store" 
        t_next "lots of electric-" 
        t_next "ity in its fur.@" 
};
static const struct DexEntry AmpharosPokedexEntry = {
    .category = "LIGHT@", // species name
    .height = 407, .weight = 1360, // height, weight
    .description = "When it gets dark,"  
        t_next "the light from its" 
        t_next "bright, shiny tail" 
        t_page "can be seen from" 
        t_next "far away on the" 
        t_next "ocean's surface.@" 
};
static const struct DexEntry BellossomPokedexEntry = {
    .category = "FLOWER@", // species name
    .height = 104, .weight = 130, // height, weight
    .description = "When these dance"  
        t_next "together, their" 
        t_next "petals rub against" 
        t_page "each other," 
        t_next "making pretty," 
        t_next "relaxing sounds.@" 
};
static const struct DexEntry MarillPokedexEntry = {
    .category = "AQUAMOUSE@", // species name
    .height = 104, .weight = 190, // height, weight
    .description = "The fur on its"  
        t_next "body naturally" 
        t_next "repels water. It" 
        t_page "can stay dry, even" 
        t_next "when it plays in" 
        t_next "the water.@" 
};
static const struct DexEntry AzumarillPokedexEntry = {
    .category = "AQUARABBIT@", // species name
    .height = 207, .weight = 630, // height, weight
    .description = "The bubble-like"  
        t_next "pattern on its" 
        t_next "stomach helps it" 
        t_page "camouflage itself" 
        t_next "when it's in the" 
        t_next "water.@" 
};
static const struct DexEntry SudowoodoPokedexEntry = {
    .category = "IMITATION@", // species name
    .height = 311, .weight = 840, // height, weight
    .description = "If a tree branch"  
        t_next "shakes when there" 
        t_next "is no wind, it's a" 
        t_page "SUDOWOODO, not a" 
        t_next "tree. It hides" 
        t_next "from the rain.@" 
};
static const struct DexEntry PolitoedPokedexEntry = {
    .category = "FROG@", // species name
    .height = 307, .weight = 750, // height, weight
    .description = "When it expands"  
        t_next "its throat to" 
        t_next "croak out a tune," 
        t_page "nearby POLIWAG and" 
        t_next "POLIWHIRL gather" 
        t_next "immediately.@" 
};
static const struct DexEntry HoppipPokedexEntry = {
    .category = "COTTONWEED@", // species name
    .height = 104, .weight = 10, // height, weight
    .description = "It can be carried"  
        t_next "away on even the" 
        t_next "gentlest breeze." 
        t_page "It may even float" 
        t_next "all the way to the" 
        t_next "next town.@" 
};
static const struct DexEntry SkiploomPokedexEntry = {
    .category = "COTTONWEED@", // species name
    .height = 200, .weight = 20, // height, weight
    .description = "As soon as it"  
        t_next "rains, it closes" 
        t_next "its flower and" 
        t_page "hides in the shade" 
        t_next "of a tree to avoid" 
        t_next "getting wet.@" 
};
static const struct DexEntry JumpluffPokedexEntry = {
    .category = "COTTONWEED@", // species name
    .height = 207, .weight = 70, // height, weight
    .description = "Even in the fierc-"  
        t_next "est wind, it can" 
        t_next "control its fluff" 
        t_page "to make its way to" 
        t_next "any place in the" 
        t_next "world it wants.@" 
};
static const struct DexEntry AipomPokedexEntry = {
    .category = "LONG TAIL@", // species name
    .height = 207, .weight = 250, // height, weight
    .description = "It uses its tail"  
        t_next "to hang on to tree" 
        t_next "branches. It uses" 
        t_page "its momentum to" 
        t_next "swing from one" 
        t_next "branch to another.@" 
};
static const struct DexEntry SunkernPokedexEntry = {
    .category = "SEED@", // species name
    .height = 100, .weight = 40, // height, weight
    .description = "It is very weak."  
        t_next "Its only means of" 
        t_next "defense is to" 
        t_page "shake its leaves" 
        t_next "desperately at its" 
        t_next "attacker.@" 
};
static const struct DexEntry SunfloraPokedexEntry = {
    .category = "SUN@", // species name
    .height = 207, .weight = 190, // height, weight
    .description = "As the hot season"  
        t_next "approaches, the" 
        t_next "petals on this" 
        t_page "#MON's face" 
        t_next "become more vivid" 
        t_next "and lively.@" 
};
static const struct DexEntry YanmaPokedexEntry = {
    .category = "CLEAR WING@", // species name
    .height = 311, .weight = 840, // height, weight
    .description = "It can see in all"  
        t_next "directions without" 
        t_next "moving its big" 
        t_page "eyes, helping it" 
        t_next "spot attackers and" 
        t_next "food right away.@" 
};
static const struct DexEntry WooperPokedexEntry = {
    .category = "WATER FISH@", // species name
    .height = 104, .weight = 190, // height, weight
    .description = "A mucous"  
        t_next "membrane covers" 
        t_next "its body. Touching" 
        t_page "it barehanded will" 
        t_next "cause a shooting" 
        t_next "pain.@" 
};
static const struct DexEntry QuagsirePokedexEntry = {
    .category = "WATER FISH@", // species name
    .height = 407, .weight = 1650, // height, weight
    .description = "Its body is always"  
        t_next "slimy. It often" 
        t_next "bangs its head on" 
        t_page "the river bottom" 
        t_next "as it swims but" 
        t_next "seems not to care.@" 
};
static const struct DexEntry EspeonPokedexEntry = {
    .category = "SUN@", // species name
    .height = 211, .weight = 580, // height, weight
    .description = "The tip of its"  
        t_next "forked tail" 
        t_next "quivers when it is" 
        t_page "predicting its" 
        t_next "opponent's next" 
        t_next "move.@" 
};
static const struct DexEntry UmbreonPokedexEntry = {
    .category = "MOONLIGHT@", // species name
    .height = 303, .weight = 600, // height, weight
    .description = "On the night of a"  
        t_next "full moon, or when" 
        t_next "it gets excited," 
        t_page "the ring patterns" 
        t_next "on its body glow" 
        t_next "yellow.@" 
};
static const struct DexEntry MurkrowPokedexEntry = {
    .category = "DARKNESS@", // species name
    .height = 108, .weight = 50, // height, weight
    .description = "It hides any shiny"  
        t_next "object it finds in" 
        t_next "a secret location." 
        t_page "MURKROW and" 
        t_next "MEOWTH loot one" 
        t_next "another's stashes.@" 
};
static const struct DexEntry SlowkingPokedexEntry = {
    .category = "ROYAL@", // species name
    .height = 607, .weight = 1750, // height, weight
    .description = "Every time it ya-"  
        t_next "wns, SHELLDER" 
        t_next "injects more poi-" 
        t_page "son into it. The" 
        t_next "poison makes it" 
        t_next "more intelligent.@" 
};
static const struct DexEntry MisdreavusPokedexEntry = {
    .category = "SCREECH@", // species name
    .height = 204, .weight = 20, // height, weight
    .description = "It loves to watch"  
        t_next "people it's scar-" 
        t_next "ed. It frightens" 
        t_page "them by screaming" 
        t_next "loudly or appear-" 
        t_next "ing suddenly.@" 
};
static const struct DexEntry UnownPokedexEntry = {
    .category = "SYMBOL@", // species name
    .height = 108, .weight = 110, // height, weight
    .description = "Because different"  
        t_next "types of UNOWN" 
        t_next "exist, it is said" 
        t_page "that they must" 
        t_next "have a variety of" 
        t_next "abilities.@" 
};
static const struct DexEntry WobbuffetPokedexEntry = {
    .category = "PATIENT@", // species name
    .height = 403, .weight = 630, // height, weight
    .description = "In order to con-"  
        t_next "ceal its black" 
        t_next "tail, it lives in" 
        t_page "a dark cave and" 
        t_next "only moves about" 
        t_next "at night.@" 
};
static const struct DexEntry GirafarigPokedexEntry = {
    .category = "LONG NECK@", // species name
    .height = 411, .weight = 910, // height, weight
    .description = "When it is in"  
        t_next "danger, its tail" 
        t_next "uses some sort of" 
        t_page "mysterious powers" 
        t_next "to drive away the" 
        t_next "enemy.@" 
};
static const struct DexEntry PinecoPokedexEntry = {
    .category = "BAGWORM@", // species name
    .height = 200, .weight = 160, // height, weight
    .description = "It spits out a"  
        t_next "fluid that it uses" 
        t_next "to glue tree bark" 
        t_page "to its body. The" 
        t_next "fluid hardens when" 
        t_next "it touches air.@" 
};
static const struct DexEntry ForretressPokedexEntry = {
    .category = "BAGWORM@", // species name
    .height = 311, .weight = 2770, // height, weight
    .description = "Usually found"  
        t_next "hanging on to a" 
        t_next "fat tree trunk. It" 
        t_page "shoots out bits of" 
        t_next "its shell when it" 
        t_next "sees action.@" 
};
static const struct DexEntry DunsparcePokedexEntry = {
    .category = "LAND SNAKE@", // species name
    .height = 411, .weight = 310, // height, weight
    .description = "It hides deep"  
        t_next "inside caves where" 
        t_next "no light ever" 
        t_page "reaches it and" 
        t_next "remains virtually" 
        t_next "motionless there.@" 
};
static const struct DexEntry GligarPokedexEntry = {
    .category = "FLYSCORPIO@", // species name
    .height = 307, .weight = 1430, // height, weight
    .description = "It builds its nest"  
        t_next "on a steep cliff." 
        t_next "When it is done" 
        t_page "gliding, it hops" 
        t_next "along the ground" 
        t_next "back to its nest.@" 
};
static const struct DexEntry SteelixPokedexEntry = {
    .category = "IRON SNAKE@", // species name
    .height = 3002, .weight = 8820, // height, weight
    .description = "The many small"  
        t_next "metal particles" 
        t_next "that cover this" 
        t_page "#MON's body" 
        t_next "reflect bright" 
        t_next "light well.@" 
};
static const struct DexEntry SnubbullPokedexEntry = {
    .category = "FAIRY@", // species name
    .height = 200, .weight = 170, // height, weight
    .description = "In truth, it is a"  
        t_next "cowardly #MON." 
        t_next "It growls eagerly" 
        t_page "in order to hide" 
        t_next "its fear from its" 
        t_next "opponent.@" 
};
static const struct DexEntry GranbullPokedexEntry = {
    .category = "FAIRY@", // species name
    .height = 407, .weight = 1070, // height, weight
    .description = "It can make most"  
        t_next "any #MON run" 
        t_next "away simply by" 
        t_page "opening its mouth" 
        t_next "wide to reveal its" 
        t_next "big fangs.@" 
};
static const struct DexEntry QwilfishPokedexEntry = {
    .category = "BALLOON@", // species name
    .height = 108, .weight = 90, // height, weight
    .description = "When faced with a"  
        t_next "larger opponent," 
        t_next "it swallows as" 
        t_page "much water as it" 
        t_next "can to match the" 
        t_next "opponent's size.@" 
};
static const struct DexEntry ScizorPokedexEntry = {
    .category = "SCISSORS@", // species name
    .height = 511, .weight = 2600, // height, weight
    .description = "This #MON's"  
        t_next "pincers, which" 
        t_next "contain steel, can" 
        t_page "crush any hard" 
        t_next "object it gets a" 
        t_next "hold of into bits.@" 
};
static const struct DexEntry ShucklePokedexEntry = {
    .category = "MOLD@", // species name
    .height = 200, .weight = 450, // height, weight
    .description = "The fluid secreted"  
        t_next "by its toes carves" 
        t_next "holes in rocks for" 
        t_page "nesting and can be" 
        t_next "mixed with BERRIES" 
        t_next "to make a drink.@" 
};
static const struct DexEntry HeracrossPokedexEntry = {
    .category = "SINGLEHORN@", // species name
    .height = 411, .weight = 1190, // height, weight
    .description = "With its Herculean"  
        t_next "powers, it can" 
        t_next "easily throw arou-" 
        t_page "nd an object that" 
        t_next "is 100 times its" 
        t_next "own weight.@" 
};
static const struct DexEntry SneaselPokedexEntry = {
    .category = "SHARP CLAW@", // species name
    .height = 211, .weight = 620, // height, weight
    .description = "This cunning"  
        t_next "#MON hides" 
        t_next "under the cover" 
        t_page "of darkness," 
        t_next "waiting to attack" 
        t_next "its prey.@" 
};
static const struct DexEntry TeddiursaPokedexEntry = {
    .category = "LITTLE BEAR@", // species name
    .height = 200, .weight = 190, // height, weight
    .description = "It always licks"  
        t_next "honey. Its palm" 
        t_next "tastes sweet" 
        t_page "because of all the" 
        t_next "honey it has" 
        t_next "absorbed.@" 
};
static const struct DexEntry UrsaringPokedexEntry = {
    .category = "HIBERNANT@", // species name
    .height = 511, .weight = 2770, // height, weight
    .description = "Although it has a"  
        t_next "large body, it is" 
        t_next "quite skilled at" 
        t_page "climbing trees. It" 
        t_next "eats and sleeps in" 
        t_next "the treetops.@" 
};
static const struct DexEntry SlugmaPokedexEntry = {
    .category = "LAVA@", // species name
    .height = 204, .weight = 770, // height, weight
    .description = "These group to-"  
        t_next "gether in areas" 
        t_next "that are hotter" 
        t_page "than normal. If it" 
        t_next "cools off, its" 
        t_next "skin hardens.@" 
};
static const struct DexEntry MagcargoPokedexEntry = {
    .category = "LAVA@", // species name
    .height = 207, .weight = 1210, // height, weight
    .description = "Its body is as hot"  
        t_next "as lava and is" 
        t_next "always billowing." 
        t_page "Flames will" 
        t_next "occasionally burst" 
        t_next "from its shell.@" 
};
static const struct DexEntry SwinubPokedexEntry = {
    .category = "PIG@", // species name
    .height = 104, .weight = 140, // height, weight
    .description = "It uses the tip of"  
        t_next "its nose to dig" 
        t_next "for food. Its nose" 
        t_page "is so tough that" 
        t_next "even frozen ground" 
        t_next "poses no problem.@" 
};
static const struct DexEntry PiloswinePokedexEntry = {
    .category = "SWINE@", // species name
    .height = 307, .weight = 1230, // height, weight
    .description = "Although its legs"  
        t_next "are short, its" 
        t_next "rugged hooves" 
        t_page "prevent it from" 
        t_next "slipping, even on" 
        t_next "icy ground.@" 
};
static const struct DexEntry CorsolaPokedexEntry = {
    .category = "CORAL@", // species name
    .height = 200, .weight = 110, // height, weight
    .description = "The points on its"  
        t_next "head absorb" 
        t_next "nutrients from" 
        t_page "clean water. They" 
        t_next "cannot survive in" 
        t_next "polluted water.@" 
};
static const struct DexEntry RemoraidPokedexEntry = {
    .category = "JET@", // species name
    .height = 200, .weight = 260, // height, weight
    .description = "To escape from an"  
        t_next "attacker, it may" 
        t_next "shoot water out of" 
        t_page "its mouth, then" 
        t_next "use that force to" 
        t_next "swim backward.@" 
};
static const struct DexEntry OctilleryPokedexEntry = {
    .category = "JET@", // species name
    .height = 211, .weight = 630, // height, weight
    .description = "Its instinct is to"  
        t_next "bury itself in" 
        t_next "holes. It often" 
        t_page "steals the nesting" 
        t_next "holes of others to" 
        t_next "sleep in them.@" 
};
static const struct DexEntry DelibirdPokedexEntry = {
    .category = "DELIVERY@", // species name
    .height = 211, .weight = 350, // height, weight
    .description = "It always carries"  
        t_next "its food with it," 
        t_next "wherever it goes." 
        t_page "If attacked, it" 
        t_next "throws its food at" 
        t_next "the opponent.@" 
};
static const struct DexEntry MantinePokedexEntry = {
    .category = "KITE@", // species name
    .height = 611, .weight = 4850, // height, weight
    .description = "It swims along"  
        t_next "freely, eating" 
        t_next "things that swim" 
        t_page "into its mouth." 
        t_next "Its whole body is" 
        t_next "very coarse.@" 
};
static const struct DexEntry SkarmoryPokedexEntry = {
    .category = "ARMOR BIRD@", // species name
    .height = 507, .weight = 1110, // height, weight
    .description = "The feathers that"  
        t_next "it sheds are very" 
        t_next "sharp. It is said" 
        t_page "that people once" 
        t_next "used the feathers" 
        t_next "as swords.@" 
};
static const struct DexEntry HoundourPokedexEntry = {
    .category = "DARK@", // species name
    .height = 200, .weight = 240, // height, weight
    .description = "Around dawn, its"  
        t_next "ominous howl" 
        t_next "echoes through the" 
        t_page "area to announce" 
        t_next "that this is its" 
        t_next "territory.@" 
};
static const struct DexEntry HoundoomPokedexEntry = {
    .category = "DARK@", // species name
    .height = 407, .weight = 770, // height, weight
    .description = "The pungent-"  
        t_next "smelling flame" 
        t_next "that shoots from" 
        t_page "its mouth results" 
        t_next "from toxins burn-" 
        t_next "ing in its body.@" 
};
static const struct DexEntry KingdraPokedexEntry = {
    .category = "DRAGON@", // species name
    .height = 511, .weight = 3350, // height, weight
    .description = "It stores energy"  
        t_next "by sleeping at" 
        t_next "underwater depths" 
        t_page "at which no other" 
        t_next "life forms can" 
        t_next "survive.@" 
};
static const struct DexEntry PhanpyPokedexEntry = {
    .category = "LONG NOSE@", // species name
    .height = 108, .weight = 740, // height, weight
    .description = "During the desert-"  
        t_next "ed morning hours," 
        t_next "it comes ashore" 
        t_page "where it deftly" 
        t_next "uses its trunk to" 
        t_next "take a shower.@" 
};
static const struct DexEntry DonphanPokedexEntry = {
    .category = "ARMOR@", // species name
    .height = 307, .weight = 2650, // height, weight
    .description = "Because this"  
        t_next "#MON's skin is" 
        t_next "so tough, a normal" 
        t_page "attack won't even" 
        t_next "leave a scratch on" 
        t_next "it.@" 
};
static const struct DexEntry Porygon2PokedexEntry = {
    .category = "VIRTUAL@", // species name
    .height = 200, .weight = 720, // height, weight
    .description = "This manmade"  
        t_next "#MON evolved" 
        t_next "from the latest" 
        t_page "technology. It" 
        t_next "may have unprog-" 
        t_next "rammed reactions.@" 
};
static const struct DexEntry StantlerPokedexEntry = {
    .category = "BIG HORN@", // species name
    .height = 407, .weight = 1570, // height, weight
    .description = "The round balls"  
        t_next "found on the" 
        t_next "fallen antlers can" 
        t_page "be ground into a" 
        t_next "powder that aids" 
        t_next "in sleeping.@" 
};
static const struct DexEntry SmearglePokedexEntry = {
    .category = "PAINTER@", // species name
    .height = 311, .weight = 1280, // height, weight
    .description = "The color of the"  
        t_next "mysterious fluid" 
        t_next "secreted from its" 
        t_page "tail is predeter-" 
        t_next "mined for each" 
        t_next "SMEARGLE.@" 
};
static const struct DexEntry TyroguePokedexEntry = {
    .category = "SCUFFLE@", // species name
    .height = 204, .weight = 460, // height, weight
    .description = "To brush up on its"  
        t_next "fighting skills," 
        t_next "it will challenge" 
        t_page "anyone. It has a" 
        t_next "very strong com-" 
        t_next "petitive spirit.@" 
};
static const struct DexEntry HitmontopPokedexEntry = {
    .category = "HANDSTAND@", // species name
    .height = 407, .weight = 1060, // height, weight
    .description = "After doing a"  
        t_next "handstand to" 
        t_next "throw off the" 
        t_page "opponent's timing," 
        t_next "it presents its" 
        t_next "fancy kick moves.@" 
};
static const struct DexEntry SmoochumPokedexEntry = {
    .category = "KISS@", // species name
    .height = 104, .weight = 130, // height, weight
    .description = "The sensitivity of"  
        t_next "its lips develops" 
        t_next "most quickly." 
        t_page "It uses them to" 
        t_next "try to identify" 
        t_next "unknown objects.@" 
};
static const struct DexEntry ElekidPokedexEntry = {
    .category = "ELECTRIC@", // species name
    .height = 200, .weight = 520, // height, weight
    .description = "It loves violent"  
        t_next "thunder. The space" 
        t_next "between its horns" 
        t_page "flickers bluish-" 
        t_next "white when it is" 
        t_next "charging energy.@" 
};
static const struct DexEntry MagbyPokedexEntry = {
    .category = "LIVE COAL@", // species name
    .height = 204, .weight = 470, // height, weight
    .description = "It naturally spits"  
        t_next "an 1100-degree" 
        t_next "flame. It is said" 
        t_page "when many appear," 
        t_next "it heralds a" 
        t_next "volcanic eruption.@" 
};
static const struct DexEntry MiltankPokedexEntry = {
    .category = "MILK COW@", // species name
    .height = 311, .weight = 1660, // height, weight
    .description = "In order to milk a"  
        t_next "MILTANK, one must" 
        t_next "have a knack for" 
        t_page "rhythmically pull-" 
        t_next "ing up and down" 
        t_next "on its udders.@" 
};
static const struct DexEntry BlisseyPokedexEntry = {
    .category = "HAPPINESS@", // species name
    .height = 411, .weight = 1030, // height, weight
    .description = "Biting into one"  
        t_next "of the delicious" 
        t_next "eggs that BLISSEY" 
        t_page "provides will make" 
        t_next "everyone around" 
        t_next "smile with joy.@" 
};
static const struct DexEntry RaikouPokedexEntry = {
    .category = "THUNDER@", // species name
    .height = 603, .weight = 3920, // height, weight
    .description = "This rough #MON"  
        t_next "stores energy" 
        t_next "inside its body," 
        t_page "then sweeps across" 
        t_next "the land, shooting" 
        t_next "off electricity.@" 
};
static const struct DexEntry EnteiPokedexEntry = {
    .category = "VOLCANO@", // species name
    .height = 607, .weight = 4370, // height, weight
    .description = "This brawny"  
        t_next "#MON courses" 
        t_next "around the earth," 
        t_page "spouting flames" 
        t_next "hotter than a" 
        t_next "volcano's magma.@" 
};
static const struct DexEntry SuicunePokedexEntry = {
    .category = "AURORA@", // species name
    .height = 607, .weight = 4120, // height, weight
    .description = "This divine"  
        t_next "#MON blows" 
        t_next "around the world," 
        t_page "always in search" 
        t_next "of a pure" 
        t_next "reservoir.@" 
};
static const struct DexEntry LarvitarPokedexEntry = {
    .category = "ROCK SKIN@", // species name
    .height = 200, .weight = 1590, // height, weight
    .description = "Born deep under-"  
        t_next "ground, this" 
        t_next "#MON becomes a" 
        t_page "pupa after eating" 
        t_next "enough dirt to" 
        t_next "make a mountain.@" 
};
static const struct DexEntry PupitarPokedexEntry = {
    .category = "HARD SHELL@", // species name
    .height = 311, .weight = 3350, // height, weight
    .description = "It will not stay"  
        t_next "still, even while" 
        t_next "it's a pupa. It" 
        t_page "already has arms" 
        t_next "and legs under its" 
        t_next "solid shell.@" 
};
static const struct DexEntry TyranitarPokedexEntry = {
    .category = "ARMOR@", // species name
    .height = 607, .weight = 4450, // height, weight
    .description = "In just one of its"  
        t_next "mighty hands, it" 
        t_next "has the power to" 
        t_page "make the ground" 
        t_next "shake and moun-" 
        t_next "tains crumble.@" 
};
static const struct DexEntry LugiaPokedexEntry = {
    .category = "DIVING@", // species name
    .height = 1701, .weight = 4760, // height, weight
    .description = "It has an incred-"  
        t_next "ible ability to" 
        t_next "calm raging sto-" 
        t_page "rms. It is said" 
        t_next "that LUGIA appears" 
        t_next "when storms start.@" 
};
static const struct DexEntry HoOhPokedexEntry = {
    .category = "RAINBOW@", // species name
    .height = 1206, .weight = 4390, // height, weight
    .description = "It will reveal"  
        t_next "itself before a" 
        t_next "pure-hearted" 
        t_page "trainer by shining" 
        t_next "its bright rain-" 
        t_next "bow-colored wings.@" 
};
static const struct DexEntry CelebiPokedexEntry = {
    .category = "TIMETRAVEL@", // species name
    .height = 200, .weight = 110, // height, weight
    .description = "Revered as a"  
        t_next "guardian of the" 
        t_next "forest, CELEBI" 
        t_page "appears wherever" 
        t_next "beautiful forests" 
        t_next "exist.@" 
};

const struct DexEntry* PokedexDataPointerTable[] = {
    &BulbasaurPokedexEntry,
    &IvysaurPokedexEntry,
    &VenusaurPokedexEntry,
    &CharmanderPokedexEntry,
    &CharmeleonPokedexEntry,
    &CharizardPokedexEntry,
    &SquirtlePokedexEntry,
    &WartortlePokedexEntry,
    &BlastoisePokedexEntry,
    &CaterpiePokedexEntry,
    &MetapodPokedexEntry,
    &ButterfreePokedexEntry,
    &WeedlePokedexEntry,
    &KakunaPokedexEntry,
    &BeedrillPokedexEntry,
    &PidgeyPokedexEntry,
    &PidgeottoPokedexEntry,
    &PidgeotPokedexEntry,
    &RattataPokedexEntry,
    &RaticatePokedexEntry,
    &SpearowPokedexEntry,
    &FearowPokedexEntry,
    &EkansPokedexEntry,
    &ArbokPokedexEntry,
    &PikachuPokedexEntry,
    &RaichuPokedexEntry,
    &SandshrewPokedexEntry,
    &SandslashPokedexEntry,
    &NidoranFPokedexEntry,
    &NidorinaPokedexEntry,
    &NidoqueenPokedexEntry,
    &NidoranMPokedexEntry,
    &NidorinoPokedexEntry,
    &NidokingPokedexEntry,
    &ClefairyPokedexEntry,
    &ClefablePokedexEntry,
    &VulpixPokedexEntry,
    &NinetalesPokedexEntry,
    &JigglypuffPokedexEntry,
    &WigglytuffPokedexEntry,
    &ZubatPokedexEntry,
    &GolbatPokedexEntry,
    &OddishPokedexEntry,
    &GloomPokedexEntry,
    &VileplumePokedexEntry,
    &ParasPokedexEntry,
    &ParasectPokedexEntry,
    &VenonatPokedexEntry,
    &VenomothPokedexEntry,
    &DiglettPokedexEntry,
    &DugtrioPokedexEntry,
    &MeowthPokedexEntry,
    &PersianPokedexEntry,
    &PsyduckPokedexEntry,
    &GolduckPokedexEntry,
    &MankeyPokedexEntry,
    &PrimeapePokedexEntry,
    &GrowlithePokedexEntry,
    &ArcaninePokedexEntry,
    &PoliwagPokedexEntry,
    &PoliwhirlPokedexEntry,
    &PoliwrathPokedexEntry,
    &AbraPokedexEntry,
    &KadabraPokedexEntry,
    &AlakazamPokedexEntry,
    &MachopPokedexEntry,
    &MachokePokedexEntry,
    &MachampPokedexEntry,
    &BellsproutPokedexEntry,
    &WeepinbellPokedexEntry,
    &VictreebelPokedexEntry,
    &TentacoolPokedexEntry,
    &TentacruelPokedexEntry,
    &GeodudePokedexEntry,
    &GravelerPokedexEntry,
    &GolemPokedexEntry,
    &PonytaPokedexEntry,
    &RapidashPokedexEntry,
    &SlowpokePokedexEntry,
    &SlowbroPokedexEntry,
    &MagnemitePokedexEntry,
    &MagnetonPokedexEntry,
    &FarfetchDPokedexEntry,
    &DoduoPokedexEntry,
    &DodrioPokedexEntry,
    &SeelPokedexEntry,
    &DewgongPokedexEntry,
    &GrimerPokedexEntry,
    &MukPokedexEntry,
    &ShellderPokedexEntry,
    &CloysterPokedexEntry,
    &GastlyPokedexEntry,
    &HaunterPokedexEntry,
    &GengarPokedexEntry,
    &OnixPokedexEntry,
    &DrowzeePokedexEntry,
    &HypnoPokedexEntry,
    &KrabbyPokedexEntry,
    &KinglerPokedexEntry,
    &VoltorbPokedexEntry,
    &ElectrodePokedexEntry,
    &ExeggcutePokedexEntry,
    &ExeggutorPokedexEntry,
    &CubonePokedexEntry,
    &MarowakPokedexEntry,
    &HitmonleePokedexEntry,
    &HitmonchanPokedexEntry,
    &LickitungPokedexEntry,
    &KoffingPokedexEntry,
    &WeezingPokedexEntry,
    &RhyhornPokedexEntry,
    &RhydonPokedexEntry,
    &ChanseyPokedexEntry,
    &TangelaPokedexEntry,
    &KangaskhanPokedexEntry,
    &HorseaPokedexEntry,
    &SeadraPokedexEntry,
    &GoldeenPokedexEntry,
    &SeakingPokedexEntry,
    &StaryuPokedexEntry,
    &StarmiePokedexEntry,
    &MrMimePokedexEntry,
    &ScytherPokedexEntry,
    &JynxPokedexEntry,
    &ElectabuzzPokedexEntry,
    &MagmarPokedexEntry,
    &PinsirPokedexEntry,
    &TaurosPokedexEntry,
    &MagikarpPokedexEntry,
    &GyaradosPokedexEntry,
    &LaprasPokedexEntry,
    &DittoPokedexEntry,
    &EeveePokedexEntry,
    &VaporeonPokedexEntry,
    &JolteonPokedexEntry,
    &FlareonPokedexEntry,
    &PorygonPokedexEntry,
    &OmanytePokedexEntry,
    &OmastarPokedexEntry,
    &KabutoPokedexEntry,
    &KabutopsPokedexEntry,
    &AerodactylPokedexEntry,
    &SnorlaxPokedexEntry,
    &ArticunoPokedexEntry,
    &ZapdosPokedexEntry,
    &MoltresPokedexEntry,
    &DratiniPokedexEntry,
    &DragonairPokedexEntry,
    &DragonitePokedexEntry,
    &MewtwoPokedexEntry,
    &MewPokedexEntry,
    &ChikoritaPokedexEntry,
    &BayleefPokedexEntry,
    &MeganiumPokedexEntry,
    &CyndaquilPokedexEntry,
    &QuilavaPokedexEntry,
    &TyphlosionPokedexEntry,
    &TotodilePokedexEntry,
    &CroconawPokedexEntry,
    &FeraligatrPokedexEntry,
    &SentretPokedexEntry,
    &FurretPokedexEntry,
    &HoothootPokedexEntry,
    &NoctowlPokedexEntry,
    &LedybaPokedexEntry,
    &LedianPokedexEntry,
    &SpinarakPokedexEntry,
    &AriadosPokedexEntry,
    &CrobatPokedexEntry,
    &ChinchouPokedexEntry,
    &LanturnPokedexEntry,
    &PichuPokedexEntry,
    &CleffaPokedexEntry,
    &IgglybuffPokedexEntry,
    &TogepiPokedexEntry,
    &TogeticPokedexEntry,
    &NatuPokedexEntry,
    &XatuPokedexEntry,
    &MareepPokedexEntry,
    &FlaaffyPokedexEntry,
    &AmpharosPokedexEntry,
    &BellossomPokedexEntry,
    &MarillPokedexEntry,
    &AzumarillPokedexEntry,
    &SudowoodoPokedexEntry,
    &PolitoedPokedexEntry,
    &HoppipPokedexEntry,
    &SkiploomPokedexEntry,
    &JumpluffPokedexEntry,
    &AipomPokedexEntry,
    &SunkernPokedexEntry,
    &SunfloraPokedexEntry,
    &YanmaPokedexEntry,
    &WooperPokedexEntry,
    &QuagsirePokedexEntry,
    &EspeonPokedexEntry,
    &UmbreonPokedexEntry,
    &MurkrowPokedexEntry,
    &SlowkingPokedexEntry,
    &MisdreavusPokedexEntry,
    &UnownPokedexEntry,
    &WobbuffetPokedexEntry,
    &GirafarigPokedexEntry,
    &PinecoPokedexEntry,
    &ForretressPokedexEntry,
    &DunsparcePokedexEntry,
    &GligarPokedexEntry,
    &SteelixPokedexEntry,
    &SnubbullPokedexEntry,
    &GranbullPokedexEntry,
    &QwilfishPokedexEntry,
    &ScizorPokedexEntry,
    &ShucklePokedexEntry,
    &HeracrossPokedexEntry,
    &SneaselPokedexEntry,
    &TeddiursaPokedexEntry,
    &UrsaringPokedexEntry,
    &SlugmaPokedexEntry,
    &MagcargoPokedexEntry,
    &SwinubPokedexEntry,
    &PiloswinePokedexEntry,
    &CorsolaPokedexEntry,
    &RemoraidPokedexEntry,
    &OctilleryPokedexEntry,
    &DelibirdPokedexEntry,
    &MantinePokedexEntry,
    &SkarmoryPokedexEntry,
    &HoundourPokedexEntry,
    &HoundoomPokedexEntry,
    &KingdraPokedexEntry,
    &PhanpyPokedexEntry,
    &DonphanPokedexEntry,
    &Porygon2PokedexEntry,
    &StantlerPokedexEntry,
    &SmearglePokedexEntry,
    &TyroguePokedexEntry,
    &HitmontopPokedexEntry,
    &SmoochumPokedexEntry,
    &ElekidPokedexEntry,
    &MagbyPokedexEntry,
    &MiltankPokedexEntry,
    &BlisseyPokedexEntry,
    &RaikouPokedexEntry,
    &EnteiPokedexEntry,
    &SuicunePokedexEntry,
    &LarvitarPokedexEntry,
    &PupitarPokedexEntry,
    &TyranitarPokedexEntry,
    &LugiaPokedexEntry,
    &HoOhPokedexEntry,
    &CelebiPokedexEntry,
};

static_assert(lengthof(PokedexDataPointerTable) == NUM_POKEMON, "");
