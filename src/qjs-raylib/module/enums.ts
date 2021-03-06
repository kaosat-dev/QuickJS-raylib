export enum ConfigFlag
{
	/** Set to show raylib logo at startup */
	FLAG_SHOW_LOGO          = 1,
	/** Set to run program in fullscreen */
	FLAG_FULLSCREEN_MODE    = 2,
	/** Set to allow resizable window */
	FLAG_WINDOW_RESIZABLE   = 4,
	/** Set to disable window decoration (frame and buttons) */
	FLAG_WINDOW_UNDECORATED = 8,
	/** Set to allow transparent window */
	FLAG_WINDOW_TRANSPARENT = 16,
	/** Set to create the window initially hidden */
	FLAG_WINDOW_HIDDEN      = 128,
	/** Set to try enabling MSAA 4X */
	FLAG_MSAA_4X_HINT       = 32,
	/** Set to try enabling V-Sync on GPU */
	FLAG_VSYNC_HINT         = 64,
}

export enum TraceLogType
{
	/** Display all logs */
	LOG_ALL = 0,
	LOG_TRACE = 1,
	LOG_DEBUG = 2,
	LOG_INFO = 3,
	LOG_WARNING = 4,
	LOG_ERROR = 5,
	LOG_FATAL = 6,
	/** Disable logging */
	LOG_NONE = 7,
}

export enum KeyboardKey
{
	// Alphanumeric keys
	KEY_APOSTROPHE      = 39,
	KEY_COMMA           = 44,
	KEY_MINUS           = 45,
	KEY_PERIOD          = 46,
	KEY_SLASH           = 47,
	KEY_ZERO            = 48,
	KEY_ONE             = 49,
	KEY_TWO             = 50,
	KEY_THREE           = 51,
	KEY_FOUR            = 52,
	KEY_FIVE            = 53,
	KEY_SIX             = 54,
	KEY_SEVEN           = 55,
	KEY_EIGHT           = 56,
	KEY_NINE            = 57,
	KEY_SEMICOLON       = 59,
	KEY_EQUAL           = 61,
	KEY_A               = 65,
	KEY_B               = 66,
	KEY_C               = 67,
	KEY_D               = 68,
	KEY_E               = 69,
	KEY_F               = 70,
	KEY_G               = 71,
	KEY_H               = 72,
	KEY_I               = 73,
	KEY_J               = 74,
	KEY_K               = 75,
	KEY_L               = 76,
	KEY_M               = 77,
	KEY_N               = 78,
	KEY_O               = 79,
	KEY_P               = 80,
	KEY_Q               = 81,
	KEY_R               = 82,
	KEY_S               = 83,
	KEY_T               = 84,
	KEY_U               = 85,
	KEY_V               = 86,
	KEY_W               = 87,
	KEY_X               = 88,
	KEY_Y               = 89,
	KEY_Z               = 90,

	// Function keys
	KEY_SPACE           = 32,
	KEY_ESCAPE          = 256,
	KEY_ENTER           = 257,
	KEY_TAB             = 258,
	KEY_BACKSPACE       = 259,
	KEY_INSERT          = 260,
	KEY_DELETE          = 261,
	KEY_RIGHT           = 262,
	KEY_LEFT            = 263,
	KEY_DOWN            = 264,
	KEY_UP              = 265,
	KEY_PAGE_UP         = 266,
	KEY_PAGE_DOWN       = 267,
	KEY_HOME            = 268,
	KEY_END             = 269,
	KEY_CAPS_LOCK       = 280,
	KEY_SCROLL_LOCK     = 281,
	KEY_NUM_LOCK        = 282,
	KEY_PRINT_SCREEN    = 283,
	KEY_PAUSE           = 284,
	KEY_F1              = 290,
	KEY_F2              = 291,
	KEY_F3              = 292,
	KEY_F4              = 293,
	KEY_F5              = 294,
	KEY_F6              = 295,
	KEY_F7              = 296,
	KEY_F8              = 297,
	KEY_F9              = 298,
	KEY_F10             = 299,
	KEY_F11             = 300,
	KEY_F12             = 301,
	KEY_LEFT_SHIFT      = 340,
	KEY_LEFT_CONTROL    = 341,
	KEY_LEFT_ALT        = 342,
	KEY_LEFT_SUPER      = 343,
	KEY_RIGHT_SHIFT     = 344,
	KEY_RIGHT_CONTROL   = 345,
	KEY_RIGHT_ALT       = 346,
	KEY_RIGHT_SUPER     = 347,
	KEY_KB_MENU         = 348,
	KEY_LEFT_BRACKET    = 91,
	KEY_BACKSLASH       = 92,
	KEY_RIGHT_BRACKET   = 93,
	KEY_GRAVE           = 96,

	// Keypad keys
	KEY_KP_0            = 320,
	KEY_KP_1            = 321,
	KEY_KP_2            = 322,
	KEY_KP_3            = 323,
	KEY_KP_4            = 324,
	KEY_KP_5            = 325,
	KEY_KP_6            = 326,
	KEY_KP_7            = 327,
	KEY_KP_8            = 328,
	KEY_KP_9            = 329,
	KEY_KP_DECIMAL      = 330,
	KEY_KP_DIVIDE       = 331,
	KEY_KP_MULTIPLY     = 332,
	KEY_KP_SUBTRACT     = 333,
	KEY_KP_ADD          = 334,
	KEY_KP_ENTER        = 335,
	KEY_KP_EQUAL        = 336,
}

export enum MouseButton
{
	MOUSE_LEFT_BUTTON   = 0,
	MOUSE_RIGHT_BUTTON  = 1,
	MOUSE_MIDDLE_BUTTON = 2,
}

export enum GamepadNumber
{
	GAMEPAD_PLAYER1     = 0,
	GAMEPAD_PLAYER2     = 1,
	GAMEPAD_PLAYER3     = 2,
	GAMEPAD_PLAYER4     = 3,
}

export enum GamepadButton
{
	// This is here just for error checking
	GAMEPAD_BUTTON_UNKNOWN = 0,

	// This is normally [A,B,X,Y]/[Circle,Triangle,Square,Cross]
	// No support for 6 button controllers though..
	GAMEPAD_BUTTON_LEFT_FACE_UP = 1,
	GAMEPAD_BUTTON_LEFT_FACE_RIGHT = 2,
	GAMEPAD_BUTTON_LEFT_FACE_DOWN = 3,
	GAMEPAD_BUTTON_LEFT_FACE_LEFT = 4,

	// This is normally a DPAD
	GAMEPAD_BUTTON_RIGHT_FACE_UP = 5,
	GAMEPAD_BUTTON_RIGHT_FACE_RIGHT = 6,
	GAMEPAD_BUTTON_RIGHT_FACE_DOWN = 7,
	GAMEPAD_BUTTON_RIGHT_FACE_LEFT = 8,

	// Triggers
	GAMEPAD_BUTTON_LEFT_TRIGGER_1 = 9,
	GAMEPAD_BUTTON_LEFT_TRIGGER_2 = 10,
	GAMEPAD_BUTTON_RIGHT_TRIGGER_1 = 11,
	GAMEPAD_BUTTON_RIGHT_TRIGGER_2 = 12,

	// These are buttons in the center of the gamepad
	/** PS3 Select */
	GAMEPAD_BUTTON_MIDDLE_LEFT = 13,
	/** PS Button/XBOX Button */
	GAMEPAD_BUTTON_MIDDLE = 14,
	/** PS3 Start */
	GAMEPAD_BUTTON_MIDDLE_RIGHT = 15,

	// These are the joystick press in buttons
	GAMEPAD_BUTTON_LEFT_THUMB = 16,
	GAMEPAD_BUTTON_RIGHT_THUMB = 17,
}

export enum ShaderLocationIndex
{
	LOC_VERTEX_POSITION = 0,
	LOC_VERTEX_TEXCOORD01 = 1,
	LOC_VERTEX_TEXCOORD02 = 2,
	LOC_VERTEX_NORMAL = 3,
	LOC_VERTEX_TANGENT = 4,
	LOC_VERTEX_COLOR = 5,
	LOC_MATRIX_MVP = 6,
	LOC_MATRIX_MODEL = 7,
	LOC_MATRIX_VIEW = 8,
	LOC_MATRIX_PROJECTION = 9,
	LOC_VECTOR_VIEW = 10,
	LOC_COLOR_DIFFUSE = 11,
	LOC_COLOR_SPECULAR = 12,
	LOC_COLOR_AMBIENT = 13,
	LOC_MAP_DIFFUSE = 14,
	LOC_MAP_ALBEDO = 14,
	LOC_MAP_SPECULAR = 15,
	LOC_MAP_METALNESS = 15,
	LOC_MAP_NORMAL = 16,
	LOC_MAP_ROUGHNESS = 17,
	LOC_MAP_OCCLUSION = 18,
	LOC_MAP_EMISSION = 19,
	LOC_MAP_HEIGHT = 20,
	LOC_MAP_CUBEMAP = 21,
	LOC_MAP_IRRADIANCE = 22,
	LOC_MAP_PREFILTER = 23,
	LOC_MAP_BRDF = 24,
}

export enum ShaderUniformDataType
{
	UNIFORM_FLOAT = 0,
	UNIFORM_VEC2 = 1,
	UNIFORM_VEC3 = 2,
	UNIFORM_VEC4 = 3,
	UNIFORM_INT = 4,
	UNIFORM_IVEC2 = 5,
	UNIFORM_IVEC3 = 6,
	UNIFORM_IVEC4 = 7,
	UNIFORM_SAMPLER2D = 8,
}

export enum MaterialMapType
{
	MAP_DIFFUSE = 0,
	MAP_ALBEDO = 0,
	MAP_SPECULAR = 1,
	MAP_METALNESS = 1,
	MAP_NORMAL    = 2,
	MAP_ROUGHNESS = 3,
	MAP_OCCLUSION = 4,
	MAP_EMISSION = 5,
	MAP_HEIGHT= 6,
	MAP_CUBEMAP = 7,             // NOTE: Uses GL_TEXTURE_CUBE_MAP
	MAP_IRRADIANCE = 8,          // NOTE: Uses GL_TEXTURE_CUBE_MAP
	MAP_PREFILTER = 9,           // NOTE: Uses GL_TEXTURE_CUBE_MAP
	MAP_BRDF = 10,
}

export enum PixelFormat
{
	UNCOMPRESSED_GRAYSCALE = 1,     // 8 bit per pixel (no alpha)
	UNCOMPRESSED_GRAY_ALPHA = 2,        // 8*2 bpp (2 channels)
	UNCOMPRESSED_R5G6B5 = 3,            // 16 bpp
	UNCOMPRESSED_R8G8B8 = 4,            // 24 bpp
	UNCOMPRESSED_R5G5B5A1 = 5,          // 16 bpp (1 bit alpha)
	UNCOMPRESSED_R4G4B4A4 = 6,          // 16 bpp (4 bit alpha)
	UNCOMPRESSED_R8G8B8A8 = 7,          // 32 bpp
	UNCOMPRESSED_R32 = 8,               // 32 bpp (1 channel - float)
	UNCOMPRESSED_R32G32B32 = 9,         // 32*3 bpp (3 channels - float)
	UNCOMPRESSED_R32G32B32A32 = 10,      // 32*4 bpp (4 channels - float)
	COMPRESSED_DXT1_RGB = 11,            // 4 bpp (no alpha)
	COMPRESSED_DXT1_RGBA = 12,           // 4 bpp (1 bit alpha)
	COMPRESSED_DXT3_RGBA = 13,           // 8 bpp
	COMPRESSED_DXT5_RGBA = 14,           // 8 bpp
	COMPRESSED_ETC1_RGB = 15,            // 4 bpp
	COMPRESSED_ETC2_RGB = 16,            // 4 bpp
	COMPRESSED_ETC2_EAC_RGBA = 17,       // 8 bpp
	COMPRESSED_PVRT_RGB = 18,            // 4 bpp
	COMPRESSED_PVRT_RGBA = 19,           // 4 bpp
	COMPRESSED_ASTC_4x4_RGBA = 20,       // 8 bpp
	COMPRESSED_ASTC_8x8_RGBA = 21,        // 2 bpp
}

export enum TextureFilterMode
{
	FILTER_POINT = 1,                   // No filter, just pixel aproximation
	FILTER_BILINEAR = 2,                // Linear filtering
	FILTER_TRILINEAR = 3,               // Trilinear filtering (linear with mipmaps)
	FILTER_ANISOTROPIC_4X = 4,          // Anisotropic filtering 4x
	FILTER_ANISOTROPIC_8X = 5,          // Anisotropic filtering 8x
	FILTER_ANISOTROPIC_16X = 6,         // Anisotropic filtering 16x
}

export enum CubemapLayoutType
{
	CUBEMAP_AUTO_DETECT = 0,            // Automatically detect layout type
	CUBEMAP_LINE_VERTICAL = 1,          // Layout is defined by a vertical line with faces
	CUBEMAP_LINE_HORIZONTAL = 2,        // Layout is defined by an horizontal line with faces
	CUBEMAP_CROSS_THREE_BY_FOUR = 3,    // Layout is defined by a 3x4 cross with cubemap faces
	CUBEMAP_CROSS_FOUR_BY_THREE = 4,    // Layout is defined by a 4x3 cross with cubemap faces
	CUBEMAP_PANORAMA = 4,               // Layout is defined by a panorama image (equirectangular map)
}

export enum TextureWrapMode
{
	WRAP_REPEAT = 0,            // Repeats texture in tiled mode
	WRAP_CLAMP = 1,             // Clamps texture to edge pixel in tiled mode
	WRAP_MIRROR_REPEAT = 2,     // Mirrors and repeats the texture in tiled mode
	WRAP_MIRROR_CLAMP = 3,      // Mirrors and clamps to border the texture in tiled mode
}

export enum FontType
{
	FONT_DEFAULT = 0,            // Default font generation, anti-aliased
	FONT_BITMAP = 1,             // Bitmap font generation, no anti-aliasing
	FONT_SDF = 2,                // SDF font generation, requires external shader
}

export enum BlendMode
{
	BLEND_ALPHA = 0,             // Blend textures considering alpha (default)
	BLEND_ADDITIVE = 1,          // Blend textures adding colors
	BLEND_MULTIPLIED = 2,        // Blend textures multiplying colors
}

export enum GestureType
{
	GESTURE_NONE        = 0,
	GESTURE_TAP         = 1,
	GESTURE_DOUBLETAP   = 2,
	GESTURE_HOLD        = 4,
	GESTURE_DRAG        = 8,
	GESTURE_SWIPE_RIGHT = 16,
	GESTURE_SWIPE_LEFT  = 32,
	GESTURE_SWIPE_UP    = 64,
	GESTURE_SWIPE_DOWN  = 128,
	GESTURE_PINCH_IN    = 256,
	GESTURE_PINCH_OUT   = 512,
}

export enum CameraMode
{
	CAMERA_CUSTOM = 0,
	CAMERA_FREE = 1,
	CAMERA_ORBITAL = 2,
	CAMERA_FIRST_PERSON = 3,
	CAMERA_THIRD_PERSON = 4,
}

export enum CameraType
{
	CAMERA_PERSPECTIVE = 0,
	CAMERA_ORTHOGRAPHIC = 1,
}

export enum NPatchType
{
	NPT_9PATCH = 0,              // Npatch defined by 3x3 tiles
	NPT_3PATCH_VERTICAL = 1,     // Npatch defined by 1x3 tiles
	NPT_3PATCH_HORIZONTAL = 2,   // Npatch defined by 3x1 tiles
}