// Very rough extension for Tiled.
// Still a work in progress.

function rgb(r, g, b) {
    return "#" + ((r * 8)).toString(16).padStart(2, '0')
        + (g * 8).toString(16).padStart(2, '0')
        + (b * 8).toString(16).padStart(2, '0');
}

const obj_pals = {
    "PAL_NPC_RED":[rgb(27,31,27), rgb(31,19,10), rgb(31, 7, 1), rgb( 0, 0, 0)], // red
    "PAL_NPC_BLUE":[rgb(27,31,27), rgb(31,19,10), rgb(10, 9,31), rgb( 0, 0, 0)], // blue
    "PAL_NPC_GREEN":[rgb(27,31,27), rgb(31,19,10), rgb( 7,23, 3), rgb( 0, 0, 0)], // green
    "PAL_NPC_BROWN":[rgb(27,31,27), rgb(31,19,10), rgb(15,10, 3), rgb( 0, 0, 0)], // brown
    "PAL_NPC_PINK":[rgb(27,31,27), rgb(31,19,10), rgb(30,10, 6), rgb( 0, 0, 0)], // pink
    "PAL_NPC_SILVER":[rgb(31,31,31), rgb(31,31,31), rgb(13,13,13), rgb( 0, 0, 0)], // silver
    "PAL_NPC_TREE":[rgb(22,31,10), rgb(12,25, 1), rgb( 5,14, 0), rgb( 7, 7, 7)], // tree
    "PAL_NPC_TEXT":[rgb(27,31,27), rgb(24,18, 7), rgb(20,15, 3), rgb( 7, 7, 7)], // rock
}

function parsePalMap(fileName) {
    var file = new TextFile(fileName, TextFile.ReadOnly);
    var string = file.readAll();

    var lines = string.split('\n');
    var i = 0;
    var palmap = []
    while(!(lines[i].includes("tilepal"))) {
        tiled.log(`${lines[i].includes("tilepal")} ? ${lines[i]}`);
        i += 1;
    }

    while(lines[i].includes("tilepal")) {
        var parts = lines[i].substring(lines[i].indexOf("tilepal") + 10).split(',');
        tiled.log(`${parts} ${parts.length}`);
        for(var part in parts) {
            switch(parts[part].trim()) {
                case 'GRAY': palmap.push(0); break;
                case 'RED': palmap.push(1); break;
                case 'GREEN': palmap.push(2); break;
                case 'WATER': palmap.push(3); break;
                case 'YELLOW': palmap.push(4); break;
                case 'BROWN': palmap.push(5); break;
                case 'ROOF': palmap.push(6); break;
            }
        }
        tiled.log(`${lines[i].includes("tilepal")} ? ${lines[i]}`);
        i += 1;
    }

    palmap.push(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)

    while(!(lines[i].includes("tilepal"))) {
        tiled.log(lines[i]);
        i += 1;
    }

    while(lines[i].includes("tilepal")) {
        var parts = lines[i].substring(lines[i].indexOf("tilepal") + 10).split(',');
        for(var part in parts) {
            switch(parts[part].trim()) {
                case 'GRAY': palmap.push(0); break;
                case 'RED': palmap.push(1); break;
                case 'GREEN': palmap.push(2); break;
                case 'WATER': palmap.push(3); break;
                case 'YELLOW': palmap.push(4); break;
                case 'BROWN': palmap.push(5); break;
                case 'ROOF': palmap.push(6); break;
            }
        }
        tiled.log(lines[i]);
        i += 1;
    }

    return palmap;
}

function readMapGroups(path) {
    var file = new TextFile(path + "/constants/map_constants.h", TextFile.ReadOnly);
    var string = file.readAll();

    var constants_string = string.substring(string.indexOf('{') + 1, string.indexOf('}'));
    var lines = string.substring(string.indexOf('}')).split('\n');

    var parts = constants_string.split(',\n');
    parts[0] = parts[0].substring(0, parts[0].indexOf('='));
    var mapgroups = {};
    var current_map_group = '';
    for(var part in parts) {
        mapgroups[parts[part].trim()] = {"index": parseInt(part) + 1, "maps": []};
    }

    var i = 1;
    while(i < lines.length) {
        while(i < lines.length && !lines[i].includes("CURRENT_MAP_GROUP")) {
            i += 1;
        }

        if(i >= lines.length)
            break;

        current_map_group = lines[i].split(' ')[2];
        i += 1;

        while(lines[i].includes("map_const")) {
            var parts = lines[i].substring(lines[i].indexOf("map_const") + 10, lines[i].lastIndexOf(")")).split(",");
            var name = parts[0].trim();
            var map_data = {
                "name": name,
                "w": parts[1].trim(),
                "h": parts[2].trim(),
                "x": parts[3].trim(),
            };
            mapgroups[current_map_group].maps[map_data.x] = map_data;
            i += 1;
        }
        i += 1;
    }
    return mapgroups;
}

function readEventASM(map, fileName) {
    const sprite_id_to_path = {
        "SPRITE_CHRIS": "/gfx/sprites/chris.png",
        "SPRITE_BUG_CATCHER": "/gfx/sprites/bug_catcher.png",
        "SPRITE_COOLTRAINER_M": "/gfx/sprites/cooltrainer_m.png",
        "SPRITE_FISHER": "/gfx/sprites/fisher.png",
        "SPRITE_FRUIT_TREE": "/gfx/sprites/fruit_tree.png",
        "SPRITE_TEACHER": "/gfx/sprites/teacher.png",
        "SPRITE_LINK_RECEPTIONIST": "/gfx/sprites/link_receptionist.png",
        "SPRITE_OFFICER": "/gfx/sprites/officer.png",
        "SPRITE_POKE_BALL": "/gfx/sprites/poke_ball.png",
        "SPRITE_YOUNGSTER": "/gfx/sprites/youngster.png",
    };
    const default_sprite_pal = {
        'SPRITE_FRUIT_TREE': 'PAL_NPC_TREE',
        'SPRITE_POKE_BALL': 'PAL_NPC_RED',
        'SPRITE_OFFICER': 'PAL_NPC_BLUE',
    };
    var sprite_table = {};
    var cur_dir = tiled.projectFilePath.substring(0, tiled.projectFilePath.lastIndexOf("/"));

    var file = new TextFile(fileName, TextFile.ReadOnly);
    var string = file.readAll();

    var lines = string.split('\n');
    var i = 0;
    var names = []
    if(lines[i].includes("object_const_def")) {
        i += 1
        while(lines[i].includes("const")) {
            names.push(lines[i].trim().split(' ')[1]);
            i += 1;
        }
    }

    while(!(lines[i].includes("def_warp_events"))) {
        i += 1;
    }

    i += 1;
    var warpLayer = new ObjectGroup("warps");
    while(lines[i].includes("warp_event")) {
        var parts = lines[i].substring(lines[i].indexOf("warp_event") + 10).split(',');
        var obj = new MapObject("");
        obj.x = parseInt(parts[0].trim()) * 16;
        obj.y = parseInt(parts[1].trim()) * 16;
        obj.width = 16;
        obj.height = 16;
        obj.className = 'warp';
        obj.setProperty('map', parts[2].trim());
        obj.setProperty('warpNum', parseInt(parts[3].trim()));
        warpLayer.addObject(obj);
        i += 1;
    }
    map.addLayer(warpLayer);

    while(!(lines[i].includes("def_coord_events"))) {
        i += 1;
    }

    i += 1;
    var coordLayer = new ObjectGroup("coords");
    while(lines[i].includes("coord_event")) {
        var parts = lines[i].substring(lines[i].indexOf("coord_event") + 11).split(',');
        var obj = new MapObject("");
        obj.x = parseInt(parts[0].trim()) * 16;
        obj.y = parseInt(parts[1].trim()) * 16;
        obj.width = 16;
        obj.height = 16;
        obj.className = 'coord';
        obj.setProperty('scene', parts[2].trim());
        obj.setProperty('script', parts[3].trim());
        coordLayer.addObject(obj);
        i += 1;
    }
    map.addLayer(coordLayer);

    while(!(lines[i].includes("def_bg_events"))) {
        i += 1;
    }

    i += 1;
    var bgLayer = new ObjectGroup("bgs");
    while(lines[i].includes("bg_event")) {
        var parts = lines[i].substring(lines[i].indexOf("bg_event") + 8).split(',');
        var obj = new MapObject("");
        obj.x = parseInt(parts[0].trim()) * 16;
        obj.y = parseInt(parts[1].trim()) * 16;
        obj.width = 16;
        obj.height = 16;
        obj.className = 'bg';
        obj.setProperty('type', parts[2].trim());
        obj.setProperty('script', parts[3].trim());
        bgLayer.addObject(obj);
        i += 1;
    }
    map.addLayer(bgLayer);

    while(!(lines[i].includes("def_object_events"))) {
        i += 1;
    }

    i += 1;
    var objLayer = new ObjectGroup("objs");
    var j = 0;
    while(lines[i].includes("object_event")) {
        var parts = lines[i].substring(lines[i].indexOf("object_event") + 12).split(',');
        var obj = new MapObject("");
        obj.x = parseInt(parts[0].trim()) * 16;
        obj.y = (parseInt(parts[1].trim()) + 1) * 16;
        obj.width = 16;
        obj.height = 16;
        obj.className = 'obj';
        obj.name = names[j];
        var sprite = parts[2].trim();
        var palette = parts[8].trim();
        if(!sprite_id_to_path.hasOwnProperty(sprite)) {
            sprite = 'SPRITE_CHRIS';
        }
        if(!obj_pals.hasOwnProperty(palette)) {
            if(!default_sprite_pal.hasOwnProperty(sprite))
                palette = 'PAL_NPC_RED';
            else
                palette = default_sprite_pal[sprite];
        }
        if(sprite_table.hasOwnProperty(sprite)) {
            obj.tile = sprite_table[sprite].tiles[0];
        }
        else {
            var sprites = new Tileset(sprite);
            sprites.setTileSize(16, 16);
            sprites.transparentColor = "#ffffff";
            sprites.image = cur_dir + sprite_id_to_path[sprite];
            var img = new Image(cur_dir + sprite_id_to_path[sprite]);
            // img.setColor(3, obj_pals[palette][0]);
            img.setColor(2, obj_pals[palette][1]);
            img.setColor(1, obj_pals[palette][2]);
            img.setColor(0, obj_pals[palette][3]);
            // img.setColor(0, rgb( 7, 7, 7));
            sprites.loadFromImage(img);
            map.addTileset(sprites);
            obj.tile = sprites.tiles[0];
            sprite_table[sprite] = sprites;
        }
        obj.setProperty('sprite', parts[2].trim());
        obj.setProperty('movement_data', parts[3].trim());
        obj.setProperty('palette', parts[8].trim());
        obj.setProperty('obj_type', parts[9].trim());
        obj.setProperty('script', parts[11].trim());
        obj.setProperty('event_flag', parts[12].trim());
        objLayer.addObject(obj);
        i += 1;
        j += 1;
    }
    map.addLayer(objLayer);
}

function applyPalette(image) {
    let pal_map = parsePalMap(image.substring(0, image.lastIndexOf(".")) + "_palette_map.asm");
    const day_pals = [
        [rgb(27,31,27), rgb(21,21,21), rgb(13,13,13), rgb( 7, 7, 7)], // gray
        [rgb(27,31,27), rgb(31,19,24), rgb(30,10, 6), rgb( 7, 7, 7)], // red
        [rgb(22,31,10), rgb(12,25, 1), rgb( 5,14, 0), rgb( 7, 7, 7)], // green
        [rgb(31,31,31), rgb( 8,12,31), rgb( 1, 4,31), rgb( 7, 7, 7)], // water
        [rgb(27,31,27), rgb(31,31, 7), rgb(31,16, 1), rgb( 7, 7, 7)], // yellow
        [rgb(27,31,27), rgb(24,18, 7), rgb(20,15, 3), rgb( 7, 7, 7)], // brown
        [rgb(27,31,27), rgb(15,31,31), rgb( 5,17,31), rgb( 7, 7, 7)], // roof
        [rgb(31,31,16), rgb(31,31,16), rgb(14, 9, 0), rgb( 0, 0, 0)], // text
    ];
    tiled.log(pal_map.length);
    var final_image = new Image(128, 128, Image.Format_RGB555);
    var img = new Image(image);
    for(var i = 0; i < 192; ++i) {
        var dx = (i % 16) * 8;
        var dy = Math.floor(i / 16) * 8;
        var copy = img.copy(dx, dy, 8, 8);
        copy.setColor(3, day_pals[pal_map[i]][0]);
        copy.setColor(2, day_pals[pal_map[i]][1]);
        copy.setColor(1, day_pals[pal_map[i]][2]);
        copy.setColor(0, day_pals[pal_map[i]][3]);
        for(var y = 0; y < 8; ++y) {
            for(var x = 0; x < 8; ++x) {
                final_image.setPixelColor(dx + x, dy + y, copy.pixelColor(x, y));
            }
        }
    }
    return final_image;
}

var binFormat = {
    name: "BIN map format",
    extension: "bin",

    read: function(fileName) {
        var cur_dir = tiled.projectFilePath.substring(0, tiled.projectFilePath.lastIndexOf("/"));
        // var dir = tiled.promptFile(tiled.projectFilePath.replace(/\/suiCune\.tile-project/, '/'), "project directory");
        var file = new BinaryFile(fileName, BinaryFile.ReadOnly);
        var bytes = new Uint8Array(file.readAll());
        var map = new TileMap();
        var tileset = new Tileset("johto");
        tileset.setTileSize(8, 8);
        var image = tiled.promptOpenFile(cur_dir + "/gfx/tilesets", "Images (*.png *.xpm *.jpg)", "Tileset image");
        tileset.image = image;
        var img = applyPalette(image);
        tileset.loadFromImage(img);
        map.addTileset(tileset);
        map.width = 4;
        map.height = (file.size + 3) / 4;
        map.tileWidth = 8;
        map.tileHeight = 8;
        var layer = new TileLayer("blocks");
        layer.width = 4;
        layer.height = (file.size + 3) / 4;
        var edit = layer.edit();
        for(let i = 0; i < file.size; i++) {
            var x = (i % 4);
            var y = (i / 4);
            edit.setTile(x, y, tileset.findTile(bytes[i]));
        }
        edit.apply();
        map.addLayer(layer);

        return map;
    },

    // write: function(map, fileName) {
        // var m = {
        //     width: map.width,
        //     height: map.height,
        //     layers: []
        // };

        // for (var i = 0; i < map.layerCount; ++i) {
        //     var layer = map.layerAt(i);
        //     if (layer.isTileLayer) {
        //         var rows = [];
        //         for (y = 0; y < layer.height; ++y) {
        //             var row = [];
        //             for (x = 0; x < layer.width; ++x)
        //                 row.push(layer.cellAt(x, y).tileId);
        //             rows.push(row);
        //         }
        //         m.layers.push(rows);
        //     }
        // }

        // var file = new BinaryFile(fileName, BinaryFile.WriteOnly);
        // file.write(JSON.stringify(m));
        // file.commit();
    // },
}

var blkFormat = {
    name: "BLK map format",
    extension: "blk",

    read: function(fileName) {
        var cur_dir = tiled.projectFilePath.substring(0, tiled.projectFilePath.lastIndexOf("/"));
        var path_to_map_id = {}
        path_to_map_id[cur_dir + "/maps/Pokecenter2F.blk"] = "POKECENTER_2F";
        path_to_map_id[cur_dir + "/maps/TradeCenter.blk"] = "TRADE_CENTER";
        path_to_map_id[cur_dir + "/maps/Colosseum.blk"] = "COLOSSEUM";
        path_to_map_id[cur_dir + "/maps/DayCare.blk"] = "DAY_CARE";
        // var dir = tiled.promptDirectory(tiled.projectFilePath.replace(/\/suiCune\.tile-project/, '/'), "project directory");
        var file = new BinaryFile(fileName, BinaryFile.ReadOnly);
        var bytes = new Uint8Array(file.readAll());
        var map = new TileMap();
        var tileset = new Tileset("johto");
        tileset.setTileSize(32, 32);
        var src = tiled.promptOpenFile(cur_dir + "/data/tilesets", "Metatiles (*_metatiles.bin)", "Metatiles");
        tileset.image = src;
        // tileset.loadFromImage(new Image(dir + "gfx/tilesets/johto.png"));
        map.addTileset(tileset);
        var mapgroups = readMapGroups(cur_dir);
        var maps = {}
        for(var key in mapgroups) {
            tiled.log(`${key}: ${mapgroups[key].index}`);
            for(var k2 in mapgroups[key].maps) {
                var k3 = mapgroups[key].maps[k2].name;
                maps[k3] = mapgroups[key].maps[k2];
                tiled.log(`    ${k3}: ${maps[k3].w}, ${maps[k3].h}`);
            }
        }
        for(var key in maps) {
            tiled.log(`    ${key}: ${maps[key].w}, ${maps[key].h}`);
        }
        if(path_to_map_id.hasOwnProperty(fileName)) {
            tiled.log(`    ${fileName}: ${path_to_map_id[fileName]}, ${maps[key].h}`);
            map.width = parseInt(maps[path_to_map_id[fileName]].w);
            map.height = parseInt(maps[path_to_map_id[fileName]].h);
        }
        else {
            var whstring = tiled.prompt("Enter the width and height of the map \"w, h\"", "30, 9").split(',');
            map.width = parseInt(whstring[0]);
            map.height = parseInt(whstring[1]);
        }
        map.tileWidth = 32;
        map.tileHeight = 32;
        var layer = new TileLayer("blocks");
        layer.width = map.width;
        layer.height = map.height;
        var edit = layer.edit();
        for(let i = 0; i < file.size; i++) {
            var x = (i % map.width);
            var y = (i / map.width);
            edit.setTile(x, y, tileset.findTile(bytes[i]));
        }
        edit.apply();
        map.addLayer(layer);

        var asmfile = fileName.substring(0, fileName.lastIndexOf(".")) + ".asm";
        readEventASM(map, asmfile);

        return map;
    },
}

tiled.registerMapFormat("bin", binFormat);
tiled.registerMapFormat("blk", blkFormat);
