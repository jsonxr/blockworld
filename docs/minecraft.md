# Example

```javascript
// acacia_log.json
{
  "parent": "minecraft:block/cube_column",
  "textures": {
    "end": "minecraft:block/acacia_log_top",
    "side": "minecraft:block/acacia_log"
  }
}

// cube_column.json
{
  "parent": "block/cube",
  "textures": {
    "particle": "#side",
    "down": "#end",
    "up": "#end",
    "north": "#side",
    "east": "#side",
    "south": "#side",
    "west": "#side"
  }
}

// cube.json
{
  "parent": "block/block",
  "elements": [
    {
      "from": [0, 0, 0],
      "to": [16, 16, 16],
      "faces": {
        "down": { "texture": "#down", "cullface": "down" },
        "up": { "texture": "#up", "cullface": "up" },
        "north": { "texture": "#north", "cullface": "north" },
        "south": { "texture": "#south", "cullface": "south" },
        "west": { "texture": "#west", "cullface": "west" },
        "east": { "texture": "#east", "cullface": "east" }
      }
    }
  ]
}

// block.json
{
  "gui_light": "side",
  "display": {
    "gui": {
      "rotation": [30, 225, 0],
      "translation": [0, 0, 0],
      "scale": [0.625, 0.625, 0.625]
    },
    "ground": {
      "rotation": [0, 0, 0],
      "translation": [0, 3, 0],
      "scale": [0.25, 0.25, 0.25]
    },
    "fixed": {
      "rotation": [0, 0, 0],
      "translation": [0, 0, 0],
      "scale": [0.5, 0.5, 0.5]
    },
    "thirdperson_righthand": {
      "rotation": [75, 45, 0],
      "translation": [0, 2.5, 0],
      "scale": [0.375, 0.375, 0.375]
    },
    "firstperson_righthand": {
      "rotation": [0, 45, 0],
      "translation": [0, 0, 0],
      "scale": [0.4, 0.4, 0.4]
    },
    "firstperson_lefthand": {
      "rotation": [0, 225, 0],
      "translation": [0, 0, 0],
      "scale": [0.4, 0.4, 0.4]
    }
  }
}

```