# Geometry Buffer

```
                              +y
                               |
                               |
                               F--------E
 A=p1.x,p2.y,p2.z             /        /|
 B=p1.x,p1.y,p2.z            /        / |
 C=p2.x,p1.y,p2.z       (u) A--------D  | <-  p2
 D=p2                       |  |     |  |
 E=p2.x,p2.y,p1.z     p1->  |  G --  |  H- - - - +x
 F=p1.x,p2.y,p1.z           | /      | /
 G=p1                       |        |/
 H=p2.x,p1.y,p1.z           B--------C (v)
                           /
                         +z

```

# Vertex - 46 bytes

1 Block = 1,656 bytes

```c++
struct Vertex {
  vec3 position;       // x,y,z (3 GLfloat)
  vec3 normal;         // x,y,z (3 GLfloat)
  vec2 uv;             // u,v (2 GLfloat)
  GLubyte light_level; // 1 byte (0-15)
  vec3 color;          // r,g,b (3 GLfloat)
  boolean biome_blend; // 1 byte?? or is it 1 bit?? (GLboolean)
}
```

- 36 vertices (6 verts/face, 6 face/cube)
- or 1248 bytes if we use elements (24 vertices + 36 uint32 elements)

# Compressed Vertex - 31 bytes

- Position - No restrictions
- Textures - 2 bytes
    - Can not adddress last row and column of the atlas
    - 65,025 unique 16px textures
    - or 16,384 unique 32px textures
    - or 3,969 unique 64px textures
- Normal - 3 bytes
    - Normals do not have to be preciese, so 0-255 probably good enough
    - Can convert to floats in the shader
- Color - 3 bytes
    - Colors are between 0-255 anyway so 3 floats are a waste at 12 bytes
    - Can convert to floats in the shader

```c++
struct VertexCompressed {
    // 12 bytes - position
  vec3 position{};    
    // 2 bytes - uv
    // 0-255 16px textures in a 4096px atlas (unused last row and col)
  uint8 texture_x{};  
  uint8 texture_y{}; 
    // 3 bytes - normal
    // Normals do not have to be precise, so 0-255 good enough
  uint8 normal_x{}; 
  uint8 normal_y{};
  uint8 normal_z{};
    // 3 bytes - color
  uint8 color_r{};     // red 0-255
  uint8 color_g{};     // green 0-255
  uint8 color_b{};     // blue 0-255
    // 1 byte - misc 
  uint8 light_level : 4 {};  // 16 values (0-15)
  boolean blend : 1 {};     // true/false
  uint8 unused : 3 {};
}
```

# Further Compression

### -65 bits - position resolution of 1/16th meter (0-256)

Shrink position from 12 bytes to 4 bytes by representing the position as an integer in the range of 0-256 and 0-4096.
this is basically the pixel resolution of a texture and how minecraft represents non-cube blocks. a 1 meter cube is
represented as [0,0,0,16,16,16].

```c++
struct VertexCompressed {
  uint8 position_x : 9 {};   // (0-256) vertex 16,256,16 = (256,4096,256)
  uint16 position_y : 13 {}; // (0-4096) vertex 16,256,16 = (256,4096,256)
  uint8 position_z : 9 {};   // (0-256) vertex 16,256,16 = (256,4096,256)
  ...
}
```

### -12 more bits - position resolution of 1 meter (0-256)

Remove 1/16th meter resolution 1 Block = 288 bytes

```c++
struct VertexCompressed {
  uint8 position_x : 5 {};  // 17 values (0-16) 16x16x256 chunk
  uint16 position_y : 9 {}; // 257 values (0-256) 16x16x256 chunk
  uint8 position_z : 5 {};  // 17 values (0-16) 16x16x256 chunk
  ...
}
```

### -21 bits - Compress normals (8 options)

Remove all lighting for faces not in the cardinal planes

```c++
struct VertexCompressed {
    uint8 normal : 3 {}; // xp,xn,yp,yn,zp,zn
    ...
}
```

### -6 bits - Compress colors (0-63)

Reduce the available color space to blend a vertex. from 16,777,216 colors to 262,144 colors

```c++
struct VertexCompressed {
  uint8 color_r : 6 {};     // red 0-63
  uint8 color_g : 6 {};     // green 0-63
  uint8 color_b : 6 {};     // blue 0-63
  ...
}
```

### -6 bits - reduce textures to 512x512

If we use a 512x512 atlas and do not use the last row and column, then we can represent the texture coordinate with
0-31,0-31. This allows for 961 unique 16x16 textures.

```c++
struct VertexCompressed {
  uint8 texture_x : 5 {};   // 0-31 16px grid in a 512x512 atlas
  uint8 texture_y : 5 {};   // 0-31 16px grid in a 512x512 atlas
  ...
}
```

# Notes

- Position and textures use an extra bit because they need to address 0-16, not 0-15.
  `00000` - `10000` and similarly 9 bits are needed to represent 0-256, not 0-255.
- These bit compressed structures are not cross platform due to Little vs Big Endian. Most modern CPUs are little endian
  while TCP/IP is Big endian.
- (byte alignment = 4 bytes/32 bits)
  [WebGL alignment 4bytes](https://webglfundamentals.org/webgl/lessons/webgl-data-textures.html)
  [Optimize OpenGL ES vertex data](https://blog.devgenius.io/optimization-of-opengl-es-vertex-data-b76927a63922)

Cubes:

- The normals for each block can only be one of six different directions so instead of sending in 3 floats at 4 bytes
  per float, we can use 3 bits to tell us which of the six normals this vertex uses

Textures:

- Similar to how we calculate the position for a cube, if we restrict it to using textures of uniform square size, we
  can calculate the uv using coordinates that are multiples of the minium size. So, 16px textures in a 1024x1024 atlas
  would be referenced as [0,0,1,1] for the first texture to
  [63,63,64,64] for the last texture. This means we can fit our coordinates into 7 bits to represent values 0-64.
- This assumes a 1024x1024 texture atlas with 16x16 square textures. Capable of supporting a 2048x2048 atlas but would
  have to ignore the last row and column because we would need an extra bit to address.

- Biome Blend can be represented as a single bit true/false. If true, it can multiply the chunk color with the texture
  to get the resulting color. Used for grass, leaves, water.
- Bit compression is not portable. But it probably doesn't matter. All modern end user hardware is little endian anyway.

  ```c++
  // Portable bitwise structs LittleEndian/BigEndian
  // This can't be used to convert little endian to network big endian bytes...
  struct Mine {
  #if __BYTE_ORDER == __LITTLE_ENDIAN
      uint8 texture_x : 5 {};
      uint8 texture_y : 5 {};
  #else
      uint8 texture_y : 5 {};
      uint8 texture_x : 5 {};
  #endif
  };
  ```

# Further Compressions...

- Reduce number of blocks in a cube and shrink the position further.
- Eliminate per vertex color and use a simple chunk biome color
- Remove biome blending
- If we only use biome blend to multiply a texture with a biome color, we could eliminate the vertex color. This would
  shrink the memory requirement down to 5 bytes. This would restrict us to only one biome blending color. I believe
  minecraft uses 1 for leaves, and a second for grass. If we stay with a per vertex color, then we could do both or even
  change water color.

# Memory Per Chunk

Average Chunk Assumptions

- "Sea level" = 64
- 10% blocks above sea level
- 10% caves below
