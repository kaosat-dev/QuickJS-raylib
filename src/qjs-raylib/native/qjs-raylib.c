#include "stdio.h"
#include "string.h"

#include "quickjs/quickjs.h"
#include "quickjs/cutils.h"
#include "raylib.h"

#include "structs.h"

#define JS_ATOM_length 48

static JSValue JS_ThrowNotImplemented(JSContext* ctx)
{
	return JS_Throw(ctx, JS_NewString(ctx, "Not implemented"));
}

// module: core
#pragma region Window-related functions

static JSValue rl_init_window(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int w, h;
	const char* title = NULL;

	if (JS_ToInt32(ctx, &w, argv[0]))
		return JS_EXCEPTION;
	
	if (JS_ToInt32(ctx, &h, argv[1]))
		return JS_EXCEPTION;

	title = JS_ToCString(ctx, argv[2]);
	if (title == NULL)
		return JS_EXCEPTION;

	InitWindow(w, h, title);

	return JS_UNDEFINED;
}

static JSValue rl_window_should_close(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewBool(ctx, WindowShouldClose());
}

static JSValue rl_close_window(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	CloseWindow();
	return JS_UNDEFINED;
}

static JSValue rl_is_window_ready(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewBool(ctx, IsWindowReady());
}

static JSValue rl_is_window_minimized(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewBool(ctx, IsWindowMinimized());
}

static JSValue rl_is_window_resized(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewBool(ctx, IsWindowResized());
}

static JSValue rl_is_window_hidden(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewBool(ctx, IsWindowHidden());
}

static JSValue rl_toggle_fullscreen(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	ToggleFullscreen();
	return JS_UNDEFINED;
}

static JSValue rl_unhide_window(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	UnhideWindow();
	return JS_UNDEFINED;
}

static JSValue rl_hide_window(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	HideWindow();
	return JS_UNDEFINED;
}

static JSValue rl_set_window_icon(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Image *icon = (Image*)JS_GetOpaque2(ctx, argv[0], js_rl_image_class_id);

	if (!icon)
		return JS_EXCEPTION;

	SetWindowIcon(*icon);
	return JS_UNDEFINED;
}

static JSValue rl_set_window_title(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* title = NULL;

	title = JS_ToCString(ctx, argv[0]);
	if (title == NULL)
		return JS_EXCEPTION;

	SetWindowTitle(title);

	return JS_UNDEFINED;
}

static JSValue rl_set_window_position(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int x, y;

	if (JS_ToInt32(ctx, &x, argv[0]))
		return JS_EXCEPTION;
	
	if (JS_ToInt32(ctx, &y, argv[1]))
		return JS_EXCEPTION;

	SetWindowPosition(x, y);

	return JS_UNDEFINED;
}

static JSValue rl_set_window_monitor(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int m;

	if (JS_ToInt32(ctx, &m, argv[0]))
		return JS_EXCEPTION;

	SetWindowMonitor(m);

	return JS_UNDEFINED;
}

static JSValue rl_set_window_min_size(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int w, h;

	if (JS_ToInt32(ctx, &w, argv[0]))
		return JS_EXCEPTION;
	
	if (JS_ToInt32(ctx, &h, argv[1]))
		return JS_EXCEPTION;

	SetWindowMinSize(w, h);

	return JS_UNDEFINED;
}

static JSValue rl_set_window_size(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int w, h;

	if (JS_ToInt32(ctx, &w, argv[0]))
		return JS_EXCEPTION;
	
	if (JS_ToInt32(ctx, &h, argv[1]))
		return JS_EXCEPTION;

	SetWindowSize(w, h);

	return JS_UNDEFINED;
}

static JSValue rl_get_screen_width(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetScreenWidth());
}

static JSValue rl_get_screen_height(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetScreenHeight());
}

static JSValue rl_get_monitor_count(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetMonitorCount());
}

static JSValue rl_get_monitor_width(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int m;

	if (JS_ToInt32(ctx, &m, argv[0]))
		return JS_EXCEPTION;

	return JS_NewInt32(ctx, GetMonitorWidth(m));
}

static JSValue rl_get_monitor_height(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int m;

	if (JS_ToInt32(ctx, &m, argv[0]))
		return JS_EXCEPTION;

	return JS_NewInt32(ctx, GetMonitorHeight(m));
}

static JSValue rl_get_monitor_physical_width(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int m;

	if (JS_ToInt32(ctx, &m, argv[0]))
		return JS_EXCEPTION;

	return JS_NewInt32(ctx, GetMonitorPhysicalWidth(m));
}

static JSValue rl_get_monitor_physical_height(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int m;

	if (JS_ToInt32(ctx, &m, argv[0]))
		return JS_EXCEPTION;

	return JS_NewInt32(ctx, GetMonitorPhysicalHeight(m));
}

static JSValue rl_get_monitor_name(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int m;

	if (JS_ToInt32(ctx, &m, argv[0]))
		return JS_EXCEPTION;

	return JS_NewString(ctx, GetMonitorName(m));
}

static JSValue rl_get_clipboard_text(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewString(ctx, GetClipboardText());
}

static JSValue rl_set_clipboard_text(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* text = NULL;

	text = JS_ToCString(ctx, argv[0]);
	if (text == NULL)
		return JS_EXCEPTION;

	SetClipboardText(text);

	return JS_UNDEFINED;
}

#pragma endregion
#pragma region Cursor-related functions

static JSValue rl_show_cursor(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	ShowCursor();
	return JS_UNDEFINED;
}

static JSValue rl_hide_cursor(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	HideCursor();
	return JS_UNDEFINED;
}

static JSValue rl_is_cursor_hidden(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewBool(ctx, IsCursorHidden());
}

static JSValue rl_enable_cursor(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	EnableCursor();
	return JS_UNDEFINED;
}

static JSValue rl_disable_cursor(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	DisableCursor();
	return JS_UNDEFINED;
}

#pragma endregion
#pragma region Drawing-related functions

static JSValue rl_clear_background(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Color color = BLACK;
	int colorInt;

	if (JS_IsNumber(argv[0]))
	{
		if (JS_ToInt32(ctx, &colorInt, argv[0])) {
			ClearBackground(color);
			return JS_UNDEFINED;
		}
		else
			color = GetColor(colorInt);
	}
	else if (JS_IsObject(argv[0]))
		color = *(Color*)JS_GetOpaque2(ctx, argv[0], js_rl_color_class_id);

	ClearBackground(color);	
	return JS_UNDEFINED;
}

static JSValue rl_begin_drawing(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	BeginDrawing();
	return JS_UNDEFINED;
}

static JSValue rl_end_drawing(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	EndDrawing();
	return JS_UNDEFINED;
}

static JSValue rl_begin_mode_2d(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Camera2D cam = *(Camera2D*)JS_GetOpaque2(ctx, argv[0], js_rl_camera2d_class_id);
	BeginMode2D(cam);
	return JS_UNDEFINED;
}

static JSValue rl_end_mode_2d(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	EndMode2D();
	return JS_UNDEFINED;
}

static JSValue rl_begin_mode_3d(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Camera3D cam = *(Camera3D*)JS_GetOpaque2(ctx, argv[0], js_rl_camera3d_class_id);
	BeginMode3D(cam);
	return JS_UNDEFINED;
}

static JSValue rl_end_mode_3d(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	EndMode3D();
	return JS_UNDEFINED;
}

static JSValue rl_begin_texture_mode(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	RenderTexture2D tex = *(RenderTexture2D*)JS_GetOpaque2(ctx, argv[0], js_rl_render_texture_class_id);
	BeginTextureMode(tex);
	return JS_UNDEFINED;
}

static JSValue rl_end_texture_mode(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	EndTextureMode();
	return JS_UNDEFINED;
}

#pragma endregion
#pragma region Screen-space-related functions

static JSValue rl_get_mouse_ray(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, js_rl_ray_class_id);
	Vector2 mousePosition = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Camera camera = *(Camera*)JS_GetOpaque2(ctx, argv[1], js_rl_camera3d_class_id);

	Ray* p = js_mallocz(ctx, sizeof(Ray));
	Ray ray = GetMouseRay(mousePosition, camera);

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	memcpy(p, &ray, sizeof(Ray));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_get_world_to_screen(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, js_rl_ray_class_id);
	Vector3 spacePos = *(Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);
	Camera camera = *(Camera3D*)JS_GetOpaque2(ctx, argv[1], js_rl_camera3d_class_id);

	Vector2* p = js_mallocz(ctx, sizeof(Vector2));
	Vector2 screenPos = GetWorldToScreen(spacePos, camera);

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	memcpy(p, &screenPos, sizeof(Vector2));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_get_camera_matrix(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, js_rl_matrix_class_id);
	Camera camera = *(Camera3D*)JS_GetOpaque2(ctx, argv[0], js_rl_camera3d_class_id);

	Matrix* p = js_mallocz(ctx, sizeof(Matrix));
	Matrix matrix = GetCameraMatrix(camera);

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	memcpy(p, &matrix, sizeof(Matrix));
	JS_SetOpaque(obj, p);

	return obj;
}

#pragma endregion
#pragma region Timing-related functions

static JSValue rl_set_target_fps(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int fps;

	if (JS_ToInt32(ctx, &fps, argv[0]))
		return JS_EXCEPTION;

	SetTargetFPS(fps);

	return JS_UNDEFINED;
}

static JSValue rl_get_fps(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetFPS());
}

static JSValue rl_get_frame_time(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewFloat64(ctx, GetFrameTime());
}

static JSValue rl_get_time(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewFloat64(ctx, GetTime());
}

#pragma endregion
#pragma region Color-related functions

static JSValue rl_color_to_int(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[0], js_rl_color_class_id);
	return JS_NewInt32(ctx, ColorToInt(color));
}

static JSValue rl_color_normalize(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[0], js_rl_color_class_id);

	Vector4* p = js_mallocz(ctx, sizeof(Vector4));
	JSValue obj = JS_NewObjectClass(ctx, js_rl_vector3_class_id);

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Vector4 vector4 = ColorNormalize(color);
	memcpy(p, &vector4, sizeof(Vector4));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_color_to_hsv(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[0], js_rl_color_class_id);
	Vector3* p = js_mallocz(ctx, sizeof(Vector3));
	Vector3 hsv = ColorToHSV(color);

	JSValue obj = JS_NewObjectClass(ctx, js_rl_vector3_class_id);

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	memcpy(p, &hsv, sizeof(Vector3));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_color_from_hsv(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3 hsv = *(Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	Color* p = js_mallocz(ctx, sizeof(Color));
	JSValue obj = JS_NewObjectClass(ctx, js_rl_color_class_id);

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Color color = ColorFromHSV(hsv);
	memcpy(p, &color, sizeof(Color));

	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_get_color(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int colorInt;

	if (JS_ToInt32(ctx, &colorInt, argv[0]))
		return JS_UNDEFINED;

	Color* p = js_mallocz(ctx, sizeof(Color));
	JSValue obj = JS_NewObjectClass(ctx, js_rl_color_class_id);

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Color color = GetColor(colorInt);
	memcpy(p, &color, sizeof(Color));

	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_fade(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[0], js_rl_color_class_id);

	Color* p = js_mallocz(ctx, sizeof(Color));
	JSValue obj = JS_NewObjectClass(ctx, js_rl_color_class_id);

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	double fade;

	if (JS_ToFloat64(ctx, &fade, argv[1]))
		return JS_EXCEPTION;

	Color newColor = Fade(color, fade);
	memcpy(p, &newColor, sizeof(Color));
	JS_SetOpaque(obj, p);

	return obj;
}

#pragma endregion
#pragma region Misc. functions

static JSValue rl_set_config_flags(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int flags;

	if (JS_ToInt32(ctx, &flags, argv[0]))
		return JS_EXCEPTION;

	SetConfigFlags((unsigned char)flags);

	return JS_UNDEFINED;
}

static JSValue rl_set_trace_log_level(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int logType;

	if (JS_ToInt32(ctx, &logType, argv[0]))
		return JS_EXCEPTION;

	SetTraceLogLevel(logType);

	return JS_UNDEFINED;
}

static JSValue rl_set_trace_log_exit(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int logType;

	if (JS_ToInt32(ctx, &logType, argv[0]))
		return JS_EXCEPTION;

	SetTraceLogExit(logType);

	return JS_UNDEFINED;
}

static JSValue rl_take_screenshot(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* fileName = JS_ToCString(ctx, argv[0]);
	if (fileName == NULL)
		return JS_EXCEPTION;

	TakeScreenshot(fileName);

	return JS_UNDEFINED;
}

static JSValue rl_get_random_value(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int min, max;

	if (JS_ToInt32(ctx, &min, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &max, argv[1]))
		return JS_EXCEPTION;

	return JS_NewInt32(ctx, GetRandomValue(min, max));
}

static JSValue rl_open_url(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* url = JS_ToCString(ctx, argv[0]);
	if (url == NULL)
		return JS_EXCEPTION;

	OpenURL(url);

	return JS_UNDEFINED;
}

#pragma endregion
#pragma region Files management functions

static JSValue rl_file_exists(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* fileName = JS_ToCString(ctx, argv[0]);
	if (fileName == NULL)
		return JS_EXCEPTION;

	return JS_NewBool(ctx, FileExists(fileName));
}

static JSValue rl_is_file_extension(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* fileName = JS_ToCString(ctx, argv[0]);
	if (fileName == NULL)
		return JS_EXCEPTION;

	const char* extension = JS_ToCString(ctx, argv[2]);
	if (extension == NULL)
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsFileExtension(fileName, extension));
}

static JSValue rl_get_extension(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* fileName = JS_ToCString(ctx, argv[0]);
	if (fileName == NULL)
		return JS_EXCEPTION;

	return JS_NewString(ctx, GetExtension(fileName));
}

static JSValue rl_get_file_name(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* filePath = JS_ToCString(ctx, argv[0]);
	if (filePath == NULL)
		return JS_EXCEPTION;

	return JS_NewString(ctx, GetFileName(filePath));
}

static JSValue rl_get_file_name_without_extension(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* filePath = JS_ToCString(ctx, argv[0]);
	if (filePath == NULL)
		return JS_EXCEPTION;

	return JS_NewString(ctx, GetFileNameWithoutExt(filePath));
}

static JSValue rl_get_directory_path(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* fileName = JS_ToCString(ctx, argv[0]);
	if (fileName == NULL)
		return JS_EXCEPTION;

	return JS_NewString(ctx, GetDirectoryPath(fileName));
}

static JSValue rl_get_working_directory(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewString(ctx, GetWorkingDirectory());
}

static JSValue rl_get_directory_files(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* dirPath = JS_ToCString(ctx, argv[0]);
	if (dirPath == NULL)
		return JS_EXCEPTION;

	int count;
	char** files = GetDirectoryFiles(dirPath, &count);

	JSValue arr = JS_NewArray(ctx);

	for (int i = 0; i < count; i++)
		JS_SetPropertyInt64(ctx, arr, i, JS_NewString(ctx, files[i]));

	ClearDirectoryFiles();

	return arr;
}

static JSValue rl_change_directory(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* dir = JS_ToCString(ctx, argv[0]);
	if (dir == NULL)
		return JS_EXCEPTION;

	return JS_NewBool(ctx, ChangeDirectory(dir));
}

static JSValue rl_is_file_dropped(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewBool(ctx, IsFileDropped());
}

static JSValue rl_get_dropped_files(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int count;
	char** files = GetDroppedFiles(&count);

	JSValue arr = JS_NewArray(ctx);

	for (int i = 0; i < count; i++)
		JS_SetPropertyInt64(ctx, arr, i, JS_NewString(ctx, files[i]));

	ClearDroppedFiles();

	return arr;
}

static JSValue rl_get_file_mod_time(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* fileName = JS_ToCString(ctx, argv[0]);
	if (fileName == NULL)
		return JS_EXCEPTION;

	return JS_NewInt64(ctx, GetFileModTime(fileName));
}

#pragma endregion
#pragma region Persistent storage management

static JSValue rl_storage_save_value(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int position, value;

	if (JS_ToInt32(ctx, &position, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &value, argv[1]))
		return JS_EXCEPTION;

	SaveStorageValue(position, value);

	return JS_UNDEFINED;
}

static JSValue rl_storage_load_value(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int position;

	if (JS_ToInt32(ctx, &position, argv[0]))
		return JS_EXCEPTION;

	return JS_NewInt32(ctx, LoadStorageValue(position));
}

#pragma endregion
#pragma region Input-related functions: keyboard

static JSValue rl_is_key_pressed(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int key;

	if (JS_ToInt32(ctx, &key, argv[0]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsKeyPressed(key));
}

static JSValue rl_is_key_down(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int key;

	if (JS_ToInt32(ctx, &key, argv[0]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsKeyDown(key));
}

static JSValue rl_is_key_released(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int key;

	if (JS_ToInt32(ctx, &key, argv[0]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsKeyReleased(key));
}

static JSValue rl_is_key_up(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int key;

	if (JS_ToInt32(ctx, &key, argv[0]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsKeyUp(key));
}

static JSValue rl_get_key_pressed(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetKeyPressed());
}

static JSValue rl_set_exit_key(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int key;

	if (JS_ToInt32(ctx, &key, argv[0]))
		return JS_EXCEPTION;

	SetExitKey(key);

	return JS_UNDEFINED;
}

#pragma endregion
#pragma region Input-related functions: gamepads

static JSValue rl_is_gamepad_available(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int gamepad;

	if (JS_ToInt32(ctx, &gamepad, argv[0]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsGamepadAvailable(gamepad));
}

static JSValue rl_is_gamepad_name(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int gamepad;

	if (JS_ToInt32(ctx, &gamepad, argv[0]))
		return JS_EXCEPTION;

	const char* name = JS_ToCString(ctx, argv[1]);
	if (name == NULL)
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsGamepadName(gamepad, name));
}

static JSValue rl_get_gamepad_name(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int gamepad;

	if (JS_ToInt32(ctx, &gamepad, argv[0]))
		return JS_EXCEPTION;

	return JS_NewString(ctx, GetGamepadName(gamepad));
}

static JSValue rl_is_gamepad_button_pressed(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int gamepad, button;

	if (JS_ToInt32(ctx, &gamepad, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &button, argv[1]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsGamepadButtonPressed(gamepad, button));
}

static JSValue rl_is_gamepad_button_down(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int gamepad, button;

	if (JS_ToInt32(ctx, &gamepad, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &button, argv[1]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsGamepadButtonDown(gamepad, button));
}

static JSValue rl_is_gamepad_button_released(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int gamepad, button;

	if (JS_ToInt32(ctx, &gamepad, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &button, argv[1]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsGamepadButtonReleased(gamepad, button));
}

static JSValue rl_is_gamepad_button_up(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int gamepad, button;

	if (JS_ToInt32(ctx, &gamepad, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &button, argv[1]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsGamepadButtonUp(gamepad, button));
}

static JSValue rl_get_gamepad_button_pressed(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetGamepadButtonPressed());
}

static JSValue rl_get_gamepad_axis_count(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int gamepad;

	if (JS_ToInt32(ctx, &gamepad, argv[0]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, GetGamepadAxisCount(gamepad));
}

static JSValue rl_get_gamepad_axis_movement(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int gamepad, axis;

	if (JS_ToInt32(ctx, &gamepad, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &axis, argv[1]))
		return JS_EXCEPTION;

	return JS_NewFloat64(ctx, GetGamepadAxisMovement(gamepad, axis));
}

#pragma endregion
#pragma region Input-related functions: mouse

static JSValue rl_is_mouse_button_pressed(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int button;

	if (JS_ToInt32(ctx, &button, argv[0]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsMouseButtonPressed(button));
}

static JSValue rl_is_mouse_button_down(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int button;

	if (JS_ToInt32(ctx, &button, argv[0]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsMouseButtonDown(button));
}

static JSValue rl_is_mouse_button_released(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int button;

	if (JS_ToInt32(ctx, &button, argv[0]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsMouseButtonReleased(button));
}

static JSValue rl_is_mouse_button_up(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int button;

	if (JS_ToInt32(ctx, &button, argv[0]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsMouseButtonUp(button));
}

static JSValue rl_get_mouse_x(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetMouseX());
}

static JSValue rl_get_mouse_y(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetMouseY());
}

static JSValue rl_get_mouse_position(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, js_rl_vector2_class_id);

	Vector2* p = js_mallocz(ctx, sizeof(Vector2));
	Vector2 mousePos = GetMousePosition();

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	memcpy(p, &mousePos, sizeof(Vector2));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_set_mouse_position(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int x, y;

	if (JS_ToInt32(ctx, &x, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &y, argv[1]))
		return JS_EXCEPTION;

	SetMousePosition(x, y);

	return JS_UNDEFINED;
}

static JSValue rl_set_mouse_offset(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int x, y;

	if (JS_ToInt32(ctx, &x, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &y, argv[1]))
		return JS_EXCEPTION;

	SetMouseOffset(x, y);

	return JS_UNDEFINED;
}

static JSValue rl_set_mouse_scale(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	double x, y;

	if (JS_ToFloat64(ctx, &x, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &y, argv[1]))
		return JS_EXCEPTION;

	SetMouseScale((float)x, (float)y);

	return JS_UNDEFINED;
}

static JSValue rl_get_mouse_wheel_move(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetMouseWheelMove());
}

#pragma endregion
#pragma region Input-related functions: touch

static JSValue rl_get_touch_x(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetTouchX());
}

static JSValue rl_get_touch_y(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetTouchY());
}

static JSValue rl_get_touch_position(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int index;

	if (JS_ToInt32(ctx, &index, argv[0]))
		return JS_EXCEPTION;

	JSValue obj = JS_NewObjectClass(ctx, js_rl_vector2_class_id);

	Vector2* p = js_mallocz(ctx, sizeof(Vector2));
	Vector2 mousePos = GetMousePosition();

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	memcpy(p, &mousePos, sizeof(Vector2));
	JS_SetOpaque(obj, p);

	return obj;
}

#pragma endregion
#pragma region Gestures and Touch Handling Functions

static JSValue rl_set_gestures_enabled(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	unsigned int flags;

	if (JS_ToUint32(ctx, &flags, argv[0]))
		return JS_EXCEPTION;

	SetGesturesEnabled(flags);

	return JS_UNDEFINED;
}

static JSValue rl_is_gesture_detected(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int gesture;

	if (JS_ToInt32(ctx, &gesture, argv[0]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, IsGestureDetected(gesture));
}

static JSValue rl_get_gesture_detected(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetGestureDetected());
}

static JSValue rl_get_touch_points_count(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewInt32(ctx, GetTouchPointsCount());
}

static JSValue rl_get_gesture_hold_duration(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewFloat64(ctx, GetGestureHoldDuration());
}

static JSValue rl_get_gesture_drag_vector(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, js_rl_vector2_class_id);

	Vector2* p = js_mallocz(ctx, sizeof(Vector2));
	Vector2 dragVector = GetGestureDragVector();

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	memcpy(p, &dragVector, sizeof(Vector2));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_get_gesture_drag_angle(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewFloat64(ctx, GetGestureDragAngle());
}

static JSValue rl_get_gesture_pinch_vector(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, js_rl_vector2_class_id);

	Vector2* p = js_mallocz(ctx, sizeof(Vector2));
	Vector2 pinchVector = GetGestureDragVector();

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	memcpy(p, &pinchVector, sizeof(Vector2));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_get_gesture_pinch_angle(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_NewFloat64(ctx, GetGesturePinchAngle());
}

#pragma endregion
#pragma region Camera System Functions

static JSValue rl_set_camera_mode(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int mode;

	if (JS_ToInt32(ctx, &mode, argv[1]))
		return JS_EXCEPTION;

	Camera camera = *(Camera*)JS_GetOpaque2(ctx, argv[0], js_rl_camera3d_class_id);

	SetCameraMode(camera, mode);

	return JS_UNDEFINED;
}

static JSValue rl_update_camera(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_rl_camera3d_class_id);
	UpdateCamera(camera);
	return JS_UNDEFINED;
}

static JSValue rl_set_camera_pan_control(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int panKey;

	if (JS_ToInt32(ctx, &panKey, argv[0]))
		return JS_EXCEPTION;

	SetCameraPanControl(panKey);

	return JS_UNDEFINED;
}

static JSValue rl_set_camera_alt_control(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int altKey;

	if (JS_ToInt32(ctx, &altKey, argv[0]))
		return JS_EXCEPTION;

	SetCameraAltControl(altKey);

	return JS_UNDEFINED;
}

static JSValue rl_set_camera_smooth_zoom_control(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int szKey;

	if (JS_ToInt32(ctx, &szKey, argv[0]))
		return JS_EXCEPTION;

	SetCameraSmoothZoomControl(szKey);

	return JS_UNDEFINED;
}

static JSValue rl_set_camera_move_controls(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int frontKey, backKey, rightKey, leftKey, upKey, downKey;

	if (JS_ToInt32(ctx, &frontKey, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &backKey, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &rightKey, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &leftKey, argv[3]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &upKey, argv[4]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &downKey, argv[5]))
		return JS_EXCEPTION;

	SetCameraMoveControls(frontKey, backKey, rightKey, leftKey, upKey, downKey);

	return JS_UNDEFINED;
}

#pragma endregion

// module: shapes
#pragma region Basic shapes drawing functions

static JSValue rl_draw_pixel(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int posX, posY;

	if (JS_ToInt32(ctx, &posX, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &posY, argv[1]))
		return JS_EXCEPTION;

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[2], js_rl_color_class_id);

	DrawPixel(posX, posY, color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_pixel_v(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 position = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[1], js_rl_color_class_id);

	DrawPixelV(position, color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_line(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int startPosX, startPosY, endPosX, endPosY;

	if (JS_ToInt32(ctx, &startPosX, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &startPosY, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &endPosX, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &endPosY, argv[3]))
		return JS_EXCEPTION;

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	DrawLine(startPosX, startPosY, endPosX, endPosY, color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_line_v(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 startPos = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Vector2 endPos = *(Vector2*)JS_GetOpaque2(ctx, argv[1], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[2], js_rl_color_class_id);

	DrawLineV(startPos, endPos, color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_line_ex(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 startPos = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Vector2 endPos = *(Vector2*)JS_GetOpaque2(ctx, argv[1], js_rl_vector2_class_id);

	double thick;

	if (JS_ToFloat64(ctx, &thick, argv[2]))
		return JS_EXCEPTION;

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[3], js_rl_color_class_id);

	DrawLineEx(startPos, endPos, thick, color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_line_bezier(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 startPos = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Vector2 endPos = *(Vector2*)JS_GetOpaque2(ctx, argv[1], js_rl_vector2_class_id);

	double thick;

	if (JS_ToFloat64(ctx, &thick, argv[2]))
		return JS_EXCEPTION;

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[3], js_rl_color_class_id);

	DrawLineBezier(startPos, endPos, thick, color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_line_strip(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue len_val = JS_GetProperty(ctx, argv[0], JS_ATOM_length);
	if (JS_IsException(len_val))
		return JS_EXCEPTION;
	
	int numPoints;

	if (JS_ToInt32(ctx, &numPoints, len_val))
		return JS_EXCEPTION;

	Vector2 points[numPoints];

	for (int i = 0; i < numPoints; i++)
	{
		JSValue value = JS_GetPropertyUint32(ctx, argv[0], i);
		points[i] = *(Vector2*)JS_GetOpaque2(ctx, value, js_rl_vector2_class_id);
	}

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[1], js_rl_color_class_id);
	DrawLineStrip(points, numPoints, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_circle(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int centerX, centerY;
	double radius;

	if (JS_ToInt32(ctx, &centerX, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &centerY, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &radius, argv[2]))
		return JS_EXCEPTION;

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[3], js_rl_color_class_id);

	DrawCircle(centerX, centerY, radius, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_circle_lines(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int centerX, centerY;
	double radius;

	if (JS_ToInt32(ctx, &centerX, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &centerY, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &radius, argv[2]))
		return JS_EXCEPTION;

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[3], js_rl_color_class_id);

	DrawCircleLines(centerX, centerY, radius, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_circle_sector(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	double radius;
	int startAngle, endAngle, segments;

	if (JS_ToFloat64(ctx, &radius, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &startAngle, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &endAngle, argv[3]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &segments, argv[4]))
		return JS_EXCEPTION;

	Vector2 center = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[5], js_rl_color_class_id);

	DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_circle_sector_lines(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	double radius;
	int startAngle, endAngle, segments;

	if (JS_ToFloat64(ctx, &radius, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &startAngle, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &endAngle, argv[3]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &segments, argv[4]))
		return JS_EXCEPTION;

	Vector2 center = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[5], js_rl_color_class_id);

	DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_circle_gradient(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int centerX, centerY;
	double radius;

	if (JS_ToInt32(ctx, &centerX, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &centerY, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &radius, argv[2]))
		return JS_EXCEPTION;

	Color color1 = *(Color*)JS_GetOpaque2(ctx, argv[3], js_rl_color_class_id);
	Color color2 = *(Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	DrawCircleGradient(centerX, centerY, radius, color1, color2);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_circle_v(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	double radius;

	if (JS_ToFloat64(ctx, &radius, argv[1]))
		return JS_EXCEPTION;

	Vector2 center = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[2], js_rl_color_class_id);

	DrawCircleV(center, radius, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_ring(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	double innerRadius, outerRadius;
	int startAngle, endAngle, segments;

	if (JS_ToFloat64(ctx, &innerRadius, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &outerRadius, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &startAngle, argv[3]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &endAngle, argv[4]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &segments, argv[5]))
		return JS_EXCEPTION;

	Vector2 center = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[6], js_rl_color_class_id);

	DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_ring_lines(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	double innerRadius, outerRadius;
	int startAngle, endAngle, segments;

	if (JS_ToFloat64(ctx, &innerRadius, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &outerRadius, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &startAngle, argv[3]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &endAngle, argv[4]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &segments, argv[5]))
		return JS_EXCEPTION;

	Vector2 center = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[6], js_rl_color_class_id);

	DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_rectangle(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int posX, posY, width, height;

	if (JS_ToInt32(ctx, &posX, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &posY, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &width, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &height, argv[3]))
		return JS_EXCEPTION;

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	DrawRectangle(posX, posY, width, height, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_rectangle_v(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 position = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Vector2 size = *(Vector2*)JS_GetOpaque2(ctx, argv[1], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[2], js_rl_color_class_id);

	DrawRectangleV(position, size, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_rectangle_rec(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Rectangle rect = *(Rectangle*)JS_GetOpaque2(ctx, argv[0], js_rl_rectangle_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[1], js_rl_color_class_id);

	DrawRectangleRec(rect, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_rectangle_pro(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	double rotation;

	if (JS_ToFloat64(ctx, &rotation, argv[2]))
		return JS_EXCEPTION;

	Rectangle rect = *(Rectangle*)JS_GetOpaque2(ctx, argv[0], js_rl_rectangle_class_id);
	Vector2 origin = *(Vector2*)JS_GetOpaque2(ctx, argv[1], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[3], js_rl_color_class_id);

	DrawRectanglePro(rect, origin, rotation, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_rectangle_gradient_v(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int posX, posY, width, height;

	if (JS_ToInt32(ctx, &posX, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &posY, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &width, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &height, argv[3]))
		return JS_EXCEPTION;

	Color color1 = *(Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);
	Color color2 = *(Color*)JS_GetOpaque2(ctx, argv[5], js_rl_color_class_id);

	DrawRectangleGradientV(posX, posY, width, height, color1, color2);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_rectangle_gradient_h(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int posX, posY, width, height;

	if (JS_ToInt32(ctx, &posX, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &posY, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &width, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &height, argv[3]))
		return JS_EXCEPTION;

	Color color1 = *(Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);
	Color color2 = *(Color*)JS_GetOpaque2(ctx, argv[5], js_rl_color_class_id);

	DrawRectangleGradientH(posX, posY, width, height, color1, color2);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_rectangle_gradient_ex(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Rectangle rect = *(Rectangle*)JS_GetOpaque2(ctx, argv[1], js_rl_rectangle_class_id);
	Color color1 = *(Color*)JS_GetOpaque2(ctx, argv[1], js_rl_color_class_id);
	Color color2 = *(Color*)JS_GetOpaque2(ctx, argv[2], js_rl_color_class_id);
	Color color3 = *(Color*)JS_GetOpaque2(ctx, argv[3], js_rl_color_class_id);
	Color color4 = *(Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	DrawRectangleGradientEx(rect, color1, color2, color3, color4);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_rectangle_lines(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int posX, posY, width, height;

	if (JS_ToInt32(ctx, &posX, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &posY, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &width, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &height, argv[3]))
		return JS_EXCEPTION;

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	DrawRectangleLines(posX, posY, width, height, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_rectangle_lines_ex(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int lineThick;

	if (JS_ToInt32(ctx, &lineThick, argv[1]))
		return JS_EXCEPTION;

	Rectangle rect = *(Rectangle*)JS_GetOpaque2(ctx, argv[0], js_rl_rectangle_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[2], js_rl_color_class_id);

	DrawRectangleLinesEx(rect, lineThick, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_rectangle_rounded(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	double roundness;
	int segments;

	if (JS_ToFloat64(ctx, &roundness, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &segments, argv[2]))
		return JS_EXCEPTION;

	Rectangle rect = *(Rectangle*)JS_GetOpaque2(ctx, argv[0], js_rl_rectangle_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[3], js_rl_color_class_id);

	DrawRectangleRounded(rect, roundness, segments, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_rectangle_rounded_lines(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	double roundness;
	int segments, lineThick;

	if (JS_ToFloat64(ctx, &roundness, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &segments, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &lineThick, argv[3]))
		return JS_EXCEPTION;

	Rectangle rect = *(Rectangle*)JS_GetOpaque2(ctx, argv[0], js_rl_rectangle_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[3], js_rl_color_class_id);

	DrawRectangleRoundedLines(rect, roundness, segments, lineThick, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_triangle(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 v1 = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Vector2 v2 = *(Vector2*)JS_GetOpaque2(ctx, argv[1], js_rl_vector2_class_id);
	Vector2 v3 = *(Vector2*)JS_GetOpaque2(ctx, argv[2], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[3], js_rl_color_class_id);

	DrawTriangle(v1, v2, v3, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_triangle_lines(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 v1 = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Vector2 v2 = *(Vector2*)JS_GetOpaque2(ctx, argv[1], js_rl_vector2_class_id);
	Vector2 v3 = *(Vector2*)JS_GetOpaque2(ctx, argv[2], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[3], js_rl_color_class_id);

	DrawTriangleLines(v1, v2, v3, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_triangle_fan(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue len_val = JS_GetProperty(ctx, argv[0], JS_ATOM_length);
	if (JS_IsException(len_val))
		return JS_EXCEPTION;
	
	int numPoints;

	if (JS_ToInt32(ctx, &numPoints, len_val))
		return JS_EXCEPTION;

	Vector2 points[numPoints];

	for (int i = 0; i < numPoints; i++)
	{
		JSValue value = JS_GetPropertyUint32(ctx, argv[0], i);
		points[i] = *(Vector2*)JS_GetOpaque2(ctx, value, js_rl_vector2_class_id);
	}

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[1], js_rl_color_class_id);
	DrawTriangleFan(points, numPoints, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_draw_poly(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	double radius, rotation;
	int sides;

	if (JS_ToInt32(ctx, &sides, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &radius, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &rotation, argv[3]))
		return JS_EXCEPTION;

	Vector2 center = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Color color = *(Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	DrawPoly(center, sides, radius, rotation, color);
	
	return JS_UNDEFINED;
}

static JSValue rl_set_shapes_texture(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Texture2D texture = *(Texture2D*)JS_GetOpaque2(ctx, argv[0], js_rl_texture2d_class_id);
	Rectangle rect = *(Rectangle*)JS_GetOpaque2(ctx, argv[1], js_rl_rectangle_class_id);

	SetShapesTexture(texture, rect);
	
	return JS_UNDEFINED;
}

#pragma endregion
#pragma region Basic shapes collision detection functions

static JSValue rl_check_collision_recs(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Rectangle rec1 = *(Rectangle*)JS_GetOpaque2(ctx, argv[0], js_rl_rectangle_class_id);
	Rectangle rec2 = *(Rectangle*)JS_GetOpaque2(ctx, argv[1], js_rl_rectangle_class_id);
	
	return JS_NewBool(ctx, CheckCollisionRecs(rec1, rec2));
}

static JSValue rl_check_collision_circles(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 center1 = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Vector2 center2 = *(Vector2*)JS_GetOpaque2(ctx, argv[2], js_rl_vector2_class_id);

	double radius1, radius2;

	if (JS_ToFloat64(ctx, &radius1, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &radius2, argv[3]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, CheckCollisionCircles(center1, radius1, center2, radius2));
}

static JSValue rl_check_collision_circle_rec(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 center = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Rectangle rec = *(Rectangle*)JS_GetOpaque2(ctx, argv[2], js_rl_rectangle_class_id);

	double radius;

	if (JS_ToFloat64(ctx, &radius, argv[1]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, CheckCollisionCircleRec(center, radius, rec));
}

static JSValue rl_get_collision_rec(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Rectangle rec1 = *(Rectangle*)JS_GetOpaque2(ctx, argv[0], js_rl_rectangle_class_id);
	Rectangle rec2 = *(Rectangle*)JS_GetOpaque2(ctx, argv[1], js_rl_rectangle_class_id);

	JSValue obj = JS_NewObjectClass(ctx, js_rl_vector2_class_id);
	Rectangle* p = js_mallocz(ctx, sizeof(Rectangle));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Rectangle coll = GetCollisionRec(rec1, rec2);
	memcpy(p, &coll, sizeof(Rectangle));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_check_collision_point_rec(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 point = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Rectangle rec = *(Rectangle*)JS_GetOpaque2(ctx, argv[1], js_rl_rectangle_class_id);

	return JS_NewBool(ctx, CheckCollisionPointRec(point, rec));
}

static JSValue rl_check_collision_point_circle(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 point = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Vector2 center = *(Vector2*)JS_GetOpaque2(ctx, argv[1], js_rl_vector2_class_id);

	double radius;

	if (JS_ToFloat64(ctx, &radius, argv[2]))
		return JS_EXCEPTION;

	return JS_NewBool(ctx, CheckCollisionPointCircle(point, center, radius));
}

static JSValue rl_check_collision_point_triangle(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector2 point = *(Vector2*)JS_GetOpaque2(ctx, argv[0], js_rl_vector2_class_id);
	Vector2 p1 = *(Vector2*)JS_GetOpaque2(ctx, argv[1], js_rl_vector2_class_id);
	Vector2 p2 = *(Vector2*)JS_GetOpaque2(ctx, argv[2], js_rl_vector2_class_id);
	Vector2 p3 = *(Vector2*)JS_GetOpaque2(ctx, argv[3], js_rl_vector2_class_id);

	return JS_NewBool(ctx, CheckCollisionPointTriangle(point, p1, p2, p3));
}

#pragma endregion

// module: textures
#pragma region Image/Texture2D data loading/unloading/saving functions

static JSValue rl_load_image(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, js_rl_image_class_id);

	if (JS_IsException(obj))
		return obj;

	const char* fileName = NULL;

	fileName = JS_ToCString(ctx, argv[0]);
	if (fileName == NULL)
		return JS_EXCEPTION;

	Image* p = js_mallocz(ctx, sizeof(Image));
	Image image = LoadImage(fileName);

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	memcpy(p, &image, sizeof(Image));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_load_image_ex(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int width, height, amount;

	if (JS_ToInt32(ctx, &width, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &height, argv[2]))
		return JS_EXCEPTION;

	amount = width * height;
	Color* pixels = js_mallocz(ctx, sizeof(Color) * amount);

	for (int i = 0; i < amount; i++)
	{
		JSValue color = JS_GetPropertyUint32(ctx, argv[0], i);
		pixels[i] = *(Color*)JS_GetOpaque2(ctx, color, js_rl_color_class_id);
	}

	JSValue obj = JS_NewObjectClass(ctx, js_rl_image_class_id);

	if (JS_IsException(obj))
		return obj;

	Image* p = js_mallocz(ctx, sizeof(Image));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Image image = LoadImageEx(pixels, width, height);
	memcpy(p, &image, sizeof(Image));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_load_image_pro(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return JS_ThrowNotImplemented(ctx);

	int width, height, format;

	if (JS_ToInt32(ctx, &width, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &height, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &format, argv[3]))
		return JS_EXCEPTION;

	// amount = width * height;

	JSValue obj = JS_NewObjectClass(ctx, js_rl_image_class_id);

	if (JS_IsException(obj))
		return obj;

	Image* p = js_mallocz(ctx, sizeof(Image));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	// Image image = LoadImagePro(pixels, width, height);
	// memcpy(p, &image, sizeof(Image));
	// JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_load_image_raw(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* fileName = NULL;

	fileName = JS_ToCString(ctx, argv[0]);
	if (fileName == NULL)
		return JS_EXCEPTION;

	int width, height, format, headerSize;

	if (JS_ToInt32(ctx, &width, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &height, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &format, argv[3]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &headerSize, argv[3]))
		return JS_EXCEPTION;

	JSValue obj = JS_NewObjectClass(ctx, js_rl_image_class_id);

	if (JS_IsException(obj))
		return obj;

	Image* p = js_mallocz(ctx, sizeof(Image));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Image image = LoadImageRaw(fileName, width, height, format, headerSize);
	memcpy(p, &image, sizeof(Image));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_export_image(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Image image = *(Image*)JS_GetOpaque2(ctx, argv[0], js_rl_image_class_id);

	const char* fileName = NULL;

	fileName = JS_ToCString(ctx, argv[1]);
	if (fileName == NULL)
		return JS_EXCEPTION;

	ExportImage(image, fileName);

	return JS_UNDEFINED;
}

static JSValue rl_export_image_as_code(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Image image = *(Image*)JS_GetOpaque2(ctx, argv[0], js_rl_image_class_id);

	const char* fileName = NULL;

	fileName = JS_ToCString(ctx, argv[1]);
	if (fileName == NULL)
		return JS_EXCEPTION;

	ExportImageAsCode(image, fileName);

	return JS_UNDEFINED;
}

static JSValue rl_load_texture(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* fileName = NULL;

	fileName = JS_ToCString(ctx, argv[0]);
	if (fileName == NULL)
		return JS_EXCEPTION;

	JSValue obj = JS_NewObjectClass(ctx, js_rl_texture2d_class_id);

	if (JS_IsException(obj))
		return obj;

	Texture2D* p = js_mallocz(ctx, sizeof(Texture2D));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Texture2D texture = LoadTexture(fileName);
	memcpy(p, &texture, sizeof(Image));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_load_texture_from_image(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, js_rl_texture2d_class_id);

	if (JS_IsException(obj))
		return obj;

	Texture2D* p = js_mallocz(ctx, sizeof(Texture2D));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Image image = *(Image*)JS_GetOpaque2(ctx, argv[0], js_rl_image_class_id);
	Texture2D texture = LoadTextureFromImage(image);
	memcpy(p, &texture, sizeof(Image));

	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_load_texture_cubemap(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Image image = *(Image*)JS_GetOpaque2(ctx, argv[0], js_rl_image_class_id);

	int layoutType;

	if (JS_ToInt32(ctx, &layoutType, argv[1]))
		return JS_EXCEPTION;

	JSValue obj = JS_NewObjectClass(ctx, js_rl_texture2d_class_id);

	if (JS_IsException(obj))
		return obj;

	Texture2D* p = js_mallocz(ctx, sizeof(Texture2D));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Texture2D texture = LoadTextureCubemap(image, layoutType);
	memcpy(p, &texture, sizeof(Image));

	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_load_render_texture(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	return js_rl_render_texture_constructor(ctx, JS_UNDEFINED, argc, argv);
}

static JSValue rl_unload_image(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Image image = *(Image*)JS_GetOpaque2(ctx, argv[0], js_rl_image_class_id);
	UnloadImage(image);
	return JS_UNDEFINED;
}

static JSValue rl_unload_texture(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Texture2D texture = *(Texture2D*)JS_GetOpaque2(ctx, argv[0], js_rl_texture2d_class_id);
	UnloadTexture(texture);
	return JS_UNDEFINED;
}

static JSValue rl_unload_render_texture(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	RenderTexture2D texture = *(RenderTexture2D*)JS_GetOpaque2(ctx, argv[0], js_rl_render_texture_class_id);
	UnloadRenderTexture(texture);
	return JS_UNDEFINED;
}

static JSValue rl_get_image_data(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Image image = *(Image*)JS_GetOpaque2(ctx, argv[0], js_rl_image_class_id);
	Color* pixels = GetImageData(image);

	int count = image.width * image.height;

	JSValue arr = JS_NewArray(ctx);

	for (int i = 0; i < count; i++)
	{
		JSValue obj = JS_NewObjectClass(ctx, js_rl_color_class_id);
		Color* pixel = js_mallocz(ctx, sizeof(Color));
		memcpy(pixel, pixels + i, sizeof(Color));
		JS_SetOpaque(obj, pixel);
		JS_SetPropertyInt64(ctx, arr, i, obj);
	}

	return arr;
}

static JSValue rl_get_image_data_normalized(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Image image = *(Image*)JS_GetOpaque2(ctx, argv[0], js_rl_image_class_id);
	Vector4* pixels = GetImageDataNormalized(image);

	int count = image.width * image.height;

	JSValue arr = JS_NewArray(ctx);

	for (int i = 0; i < count; i++)
	{
		JSValue obj = JS_NewObjectClass(ctx, js_rl_vector4_class_id);
		Vector4* pixel = js_mallocz(ctx, sizeof(Vector4));
		memcpy(pixel, pixels + i, sizeof(Vector4));
		JS_SetOpaque(obj, pixel);
		JS_SetPropertyInt64(ctx, arr, i, obj);
	}

	return arr;
}

static JSValue rl_get_pixel_data_size(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int width, height, format;

	if (JS_ToInt32(ctx, &width, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &height, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &format, argv[2]))
		return JS_EXCEPTION;

	return JS_NewInt32(ctx, GetPixelDataSize(width, height, format));
}

static JSValue rl_get_texture_data(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, js_rl_image_class_id);

	if (JS_IsException(obj))
		return obj;

	Image* p = js_mallocz(ctx, sizeof(Image));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Texture2D texture = *(Texture2D*)JS_GetOpaque2(ctx, argv[0], js_rl_texture2d_class_id);
	Image image = GetTextureData(texture);
	memcpy(p, &image, sizeof(Image));

	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_get_screen_data(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, js_rl_image_class_id);

	if (JS_IsException(obj))
		return obj;

	Image* p = js_mallocz(ctx, sizeof(Image));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Image image = GetScreenData();
	memcpy(p, &image, sizeof(Image));

	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_update_texture(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Texture2D texture = *(Texture2D*)JS_GetOpaque2(ctx, argv[0], js_rl_texture2d_class_id);

	int count = texture.width * texture.height;
	unsigned char* pixels = js_mallocz(ctx, sizeof(unsigned char) * count);

	for (int i = 0; i < count; i++)
	{
		JSValue obj = JS_GetPropertyUint32(ctx, argv[1], i);
		int pixel;
		if (JS_ToInt32(ctx, &pixel, obj))
			return JS_EXCEPTION;
		pixels[i] = (unsigned char)pixel;
	}
	
	UpdateTexture(texture, pixels);

	return JS_UNDEFINED;
}

#pragma endregion

// module: text
#pragma region Font loading/unloading functions

static JSValue rl_get_font_default(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, js_rl_font_class_id);
	Font* p = js_mallocz(ctx, sizeof(Font));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Font font = GetFontDefault();
	memcpy(p, &font, sizeof(Font));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_load_font(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* fileName = NULL;
	fileName = JS_ToCString(ctx, argv[0]);

	if (fileName == NULL)
		return JS_EXCEPTION;

	JSValue obj = JS_NewObjectClass(ctx, js_rl_font_class_id);
	Font* p = js_mallocz(ctx, sizeof(Font));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Font font = LoadFont(fileName);
	memcpy(p, &font, sizeof(Font));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_load_font_ex(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* fileName = NULL;
	fileName = JS_ToCString(ctx, argv[0]);

	if (fileName == NULL)
		return JS_EXCEPTION;

	int fontSize, charsCount;

	if (JS_ToInt32(ctx, &fontSize, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &charsCount, argv[3]))
		return JS_EXCEPTION;

	int fontChars[charsCount];

	for (int i = 0; i < charsCount; i++)
	{
		JSValue value = JS_GetPropertyUint32(ctx, argv[2], i);

		if (JS_ToInt32(ctx, fontChars + i, value))
			return JS_EXCEPTION;
	}

	JSValue obj = JS_NewObjectClass(ctx, js_rl_font_class_id);
	Font* p = js_mallocz(ctx, sizeof(Font));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Font font = LoadFontEx(fileName, fontSize, fontChars, charsCount);
	memcpy(p, &font, sizeof(Font));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_load_font_data(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* fileName = NULL;
	fileName = JS_ToCString(ctx, argv[0]);

	if (fileName == NULL)
		return JS_EXCEPTION;

	int fontSize, charsCount, type;

	if (JS_ToInt32(ctx, &fontSize, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &charsCount, argv[3]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &type, argv[4]))
		return JS_EXCEPTION;

	int fontChars[charsCount];

	for (int i = 0; i < charsCount; i++)
	{
		JSValue value = JS_GetPropertyUint32(ctx, argv[2], i);

		if (JS_ToInt32(ctx, fontChars + i, value))
			return JS_EXCEPTION;
	}

	CharInfo* p = js_mallocz(ctx, sizeof(CharInfo) * charsCount);
	JSValue arr = JS_NewArray(ctx);

	if (!p)
	{
		JS_FreeValue(ctx, arr);
		return JS_EXCEPTION;
	}

	CharInfo* chars = LoadFontData(fileName, fontSize, fontChars, charsCount, type);
	memcpy(p, chars, sizeof(CharInfo) * charsCount);

	for (int i = 0; i < charsCount; i++)
	{
		JSValue value = JS_NewObjectClass(ctx, js_rl_char_info_class_id);
		JS_SetOpaque(value, p + i);
		JS_SetPropertyUint32(ctx, arr, i, value);
	}

	return arr;
}

static JSValue rl_load_font_from_image(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Image image = *(Image*)JS_GetOpaque2(ctx, argv[0], js_rl_image_class_id);
	Color key = *(Color*)JS_GetOpaque2(ctx, argv[1], js_rl_color_class_id);

	int firstChar;

	if (JS_ToInt32(ctx, &firstChar, argv[2]))
		return JS_EXCEPTION;

	JSValue obj = JS_NewObjectClass(ctx, js_rl_font_class_id);
	Font* p = js_mallocz(ctx, sizeof(Font));

	if (!p)
	{
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Font font = LoadFontFromImage(image, key, firstChar);
	memcpy(p, &font, sizeof(Font));
	JS_SetOpaque(obj, p);

	return obj;
}

/*static JSValue rl_get_image_font_atlas(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int charsCount, fontSize, padding, packMethod;

	if (JS_ToInt32(ctx, &charsCount, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &fontSize, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &padding, argv[3]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &packMethod, argv[4]))
		return JS_EXCEPTION;

	CharInfo* chars = (CharInfo*)js_mallocz(ctx, sizeof(CharInfo) * charsCount);

	for (int i = 0; i < charsCount; i++)
	{
		JSValue value = JS_GetPropertyUint32(ctx, argv[0], i);
		chars[i] = *(CharInfo*)JS_GetOpaque2(ctx, value, js_rl_char_info_class_id);
	}

	JSValue obj = JS_NewObjectClass(ctx, js_rl_image_class_id);
	Image* p = js_mallocz(ctx, sizeof(Image));

	if (!p)
	{
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Image atlas = GenImageFontAtlas(chars, charsCount, fontSize, padding, packMethod);
	memcpy(p, &atlas, sizeof(Image));
	JS_SetOpaque(obj, p);

	return obj;
}*/

static JSValue rl_unload_font(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Font font = *(Font*)JS_GetOpaque2(ctx, argv[0], js_rl_font_class_id);
	UnloadFont(font);
	return JS_UNDEFINED;
}

#pragma endregion
#pragma region Text drawing functions

static JSValue rl_draw_fps(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int x, y;

	if (JS_ToInt32(ctx, &x, argv[0]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &y, argv[1]))
		return JS_EXCEPTION;

	DrawFPS(x, y);

	return JS_UNDEFINED;
}

static JSValue rl_draw_text(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* text = NULL;
	int x, y, size, colorInt;
	Color color = WHITE;
	
	text = JS_ToCString(ctx, argv[0]);
	if (text == NULL)
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &x, argv[1]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &y, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &size, argv[3]))
		return JS_EXCEPTION;

	if (JS_IsNumber(argv[4]))
	{
		if (JS_ToInt32(ctx, &colorInt, argv[4]))
			return JS_EXCEPTION;
		else
			color = GetColor(colorInt);
	}
	else if (JS_IsObject(argv[4]))
		color = *(Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	DrawText(text, x, y, size, color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_text_ex(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Font font = *(Font*)JS_GetOpaque2(ctx, argv[0], js_rl_font_class_id);

	const char* text = NULL;
	
	text = JS_ToCString(ctx, argv[1]);
	if (text == NULL)
		return JS_EXCEPTION;

	Vector2 position = *(Vector2*)JS_GetOpaque2(ctx, argv[2], js_rl_vector2_class_id);

	double fontSize, spacing;

	if (JS_ToFloat64(ctx, &fontSize, argv[3]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &spacing, argv[4]))
		return JS_EXCEPTION;

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[5], js_rl_color_class_id);

	DrawTextEx(font, text, position, fontSize, spacing, color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_text_rec(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Font font = *(Font*)JS_GetOpaque2(ctx, argv[0], js_rl_font_class_id);

	const char* text = NULL;
	
	text = JS_ToCString(ctx, argv[1]);
	if (text == NULL)
		return JS_EXCEPTION;

	Rectangle rec = *(Rectangle*)JS_GetOpaque2(ctx, argv[2], js_rl_rectangle_class_id);

	double fontSize, spacing;

	if (JS_ToFloat64(ctx, &fontSize, argv[3]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &spacing, argv[4]))
		return JS_EXCEPTION;

	bool wordWrap = JS_ToBool(ctx, argv[5]);

	Color color = *(Color*)JS_GetOpaque2(ctx, argv[6], js_rl_color_class_id);

	DrawTextRec(font, text, rec, fontSize, spacing, wordWrap, color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_text_rec_ex(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Font font = *(Font*)JS_GetOpaque2(ctx, argv[0], js_rl_font_class_id);

	const char* text = NULL;
	
	text = JS_ToCString(ctx, argv[1]);
	if (text == NULL)
		return JS_EXCEPTION;

	Rectangle rec = *(Rectangle*)JS_GetOpaque2(ctx, argv[2], js_rl_rectangle_class_id);

	double fontSize, spacing;

	if (JS_ToFloat64(ctx, &fontSize, argv[3]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &spacing, argv[4]))
		return JS_EXCEPTION;

	bool wordWrap = JS_ToBool(ctx, argv[5]);

	Color tint = *(Color*)JS_GetOpaque2(ctx, argv[6], js_rl_color_class_id);

	int selectStart, selectLength;

	if (JS_ToInt32(ctx, &selectStart, argv[7]))
		return JS_EXCEPTION;

	if (JS_ToInt32(ctx, &selectLength, argv[8]))
		return JS_EXCEPTION;

	Color selectText = *(Color*)JS_GetOpaque2(ctx, argv[9], js_rl_color_class_id);
	Color selectBack = *(Color*)JS_GetOpaque2(ctx, argv[10], js_rl_color_class_id);

	DrawTextRecEx(font, text, rec, fontSize, spacing, wordWrap, tint, selectStart, selectLength, selectText, selectBack);

	return JS_UNDEFINED;
}

#pragma endregion
#pragma region Text misc. functions

static JSValue rl_measure_text(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	const char* text = NULL;
	
	text = JS_ToCString(ctx, argv[0]);
	if (text == NULL)
		return JS_EXCEPTION;

	int fontSize;

	if (JS_ToInt32(ctx, &fontSize, argv[1]))
		return JS_EXCEPTION;

	return JS_NewInt32(ctx, MeasureText(text, fontSize));
}

static JSValue rl_measure_text_ex(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Font font = *(Font*)JS_GetOpaque2(ctx, argv[0], js_rl_font_class_id);

	const char* text = NULL;
	
	text = JS_ToCString(ctx, argv[1]);
	if (text == NULL)
		return JS_EXCEPTION;

	double fontSize, spacing;

	if (JS_ToFloat64(ctx, &fontSize, argv[2]))
		return JS_EXCEPTION;

	if (JS_ToFloat64(ctx, &spacing, argv[3]))
		return JS_EXCEPTION;

	JSValue obj = JS_NewObjectClass(ctx, js_rl_vector2_class_id);
	Vector2* p = js_mallocz(ctx, sizeof(Vector2));

	if (!p) {
		JS_FreeValue(ctx, obj);
		return JS_EXCEPTION;
	}

	Vector2 coll = MeasureTextEx(font, text, fontSize, spacing);
	memcpy(p, &coll, sizeof(Vector2));
	JS_SetOpaque(obj, p);

	return obj;
}

static JSValue rl_get_glyph_index(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Font font = *(Font*)JS_GetOpaque2(ctx, argv[0], js_rl_font_class_id);

	int character;

	if (JS_ToInt32(ctx, &character, argv[1]))
		return JS_EXCEPTION;

	return JS_NewInt32(ctx, GetGlyphIndex(font, character));
}

#pragma endregion

// module: models
#pragma region Basic geometric 3D shapes drawing functions

static JSValue rl_draw_line_3d(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* start = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!start)
		return JS_EXCEPTION;

	Vector3* end = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_rl_vector3_class_id);

	if (!end)
		return JS_EXCEPTION;

	Color* color = (Color*)JS_GetOpaque2(ctx, argv[2], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;


	DrawLine3D(*start, *end, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_point_3d(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* pos = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!pos)
		return JS_EXCEPTION;

	Color* color = (Color*)JS_GetOpaque2(ctx, argv[1], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawPoint3D(*pos, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_circle_3d(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* center = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!center)
		return JS_EXCEPTION;

	double radius;

	if (JS_ToFloat64(ctx, &radius, argv[1]))
		return JS_EXCEPTION;

	Vector3* rotationAxis = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_rl_vector3_class_id);

	if (!rotationAxis)
		return JS_EXCEPTION;

	double rotationAngle;

	if (JS_ToFloat64(ctx, &rotationAngle, argv[3]))
		return JS_EXCEPTION;
	
	Color* color = (Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawCircle3D(*center, radius, *rotationAxis, rotationAngle, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_cube(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* position = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!position)
		return JS_EXCEPTION;

	double width;

	if (JS_ToFloat64(ctx, &width, argv[1]))
		return JS_EXCEPTION;

	double height;

	if (JS_ToFloat64(ctx, &height, argv[2]))
		return JS_EXCEPTION;

	double length;

	if (JS_ToFloat64(ctx, &length, argv[3]))
		return JS_EXCEPTION;
	
	Color* color = (Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawCube(*position, width, height, length, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_cube_wires(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* position = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!position)
		return JS_EXCEPTION;

	double width;

	if (JS_ToFloat64(ctx, &width, argv[1]))
		return JS_EXCEPTION;

	double height;

	if (JS_ToFloat64(ctx, &height, argv[2]))
		return JS_EXCEPTION;

	double length;

	if (JS_ToFloat64(ctx, &length, argv[3]))
		return JS_EXCEPTION;
	
	Color* color = (Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawCubeWires(*position, width, height, length, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_cube_v(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* position = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!position)
		return JS_EXCEPTION;

	Vector3* size = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_rl_vector3_class_id);

	if (!size)
		return JS_EXCEPTION;

	Color* color = (Color*)JS_GetOpaque2(ctx, argv[2], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;


	DrawCubeV(*position, *size, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_cube_wires_v(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* position = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!position)
		return JS_EXCEPTION;

	Vector3* size = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_rl_vector3_class_id);

	if (!size)
		return JS_EXCEPTION;

	Color* color = (Color*)JS_GetOpaque2(ctx, argv[2], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawCubeWiresV(*position, *size, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_cube_texture(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Texture* texture = (Texture*)JS_GetOpaque2(ctx, argv[0], js_rl_texture2d_class_id);

	if (!texture)
		return JS_EXCEPTION;
	
	Vector3* position = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_rl_vector3_class_id);

	if (!position)
		return JS_EXCEPTION;

	double width;

	if (JS_ToFloat64(ctx, &width, argv[2]))
		return JS_EXCEPTION;

	double height;

	if (JS_ToFloat64(ctx, &height, argv[3]))
		return JS_EXCEPTION;

	double length;

	if (JS_ToFloat64(ctx, &length, argv[4]))
		return JS_EXCEPTION;
	
	Color* color = (Color*)JS_GetOpaque2(ctx, argv[5], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawCubeTexture(*texture, *position, width, height, length, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_sphere(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* center = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!center)
		return JS_EXCEPTION;

	double radius;

	if (JS_ToFloat64(ctx, &radius, argv[1]))
		return JS_EXCEPTION;
	
	Color* color = (Color*)JS_GetOpaque2(ctx, argv[2], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawSphere(*center, radius, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_sphere_ex(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* center = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!center)
		return JS_EXCEPTION;

	double radius;

	if (JS_ToFloat64(ctx, &radius, argv[1]))
		return JS_EXCEPTION;

	int rings;

	if (JS_ToInt32(ctx, &rings, argv[2]))
		return JS_EXCEPTION;

	int slices;

	if (JS_ToInt32(ctx, &slices, argv[3]))
		return JS_EXCEPTION;
	
	Color* color = (Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawSphereEx(*center, radius, rings, slices, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_sphere_wires(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* center = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!center)
		return JS_EXCEPTION;

	double radius;

	if (JS_ToFloat64(ctx, &radius, argv[1]))
		return JS_EXCEPTION;

	int rings;

	if (JS_ToInt32(ctx, &rings, argv[2]))
		return JS_EXCEPTION;

	int slices;

	if (JS_ToInt32(ctx, &slices, argv[3]))
		return JS_EXCEPTION;
	
	Color* color = (Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawSphereWires(*center, radius, rings, slices, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_cylinder(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* position = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!position)
		return JS_EXCEPTION;

	double radiusTop;

	if (JS_ToFloat64(ctx, &radiusTop, argv[1]))
		return JS_EXCEPTION;

	double radiusBottom;

	if (JS_ToFloat64(ctx, &radiusBottom, argv[2]))
		return JS_EXCEPTION;

	double height;

	if (JS_ToFloat64(ctx, &height, argv[3]))
		return JS_EXCEPTION;

	int slices;

	if (JS_ToInt32(ctx, &slices, argv[3]))
		return JS_EXCEPTION;
	
	Color* color = (Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawCylinder(*position, radiusTop, radiusBottom, height, slices, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_cylinder_wires(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* position = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!position)
		return JS_EXCEPTION;

	double radiusTop;

	if (JS_ToFloat64(ctx, &radiusTop, argv[1]))
		return JS_EXCEPTION;

	double radiusBottom;

	if (JS_ToFloat64(ctx, &radiusBottom, argv[2]))
		return JS_EXCEPTION;

	double height;

	if (JS_ToFloat64(ctx, &height, argv[3]))
		return JS_EXCEPTION;

	int slices;

	if (JS_ToInt32(ctx, &slices, argv[3]))
		return JS_EXCEPTION;
	
	Color* color = (Color*)JS_GetOpaque2(ctx, argv[4], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawCylinderWires(*position, radiusTop, radiusBottom, height, slices, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_plane(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* center = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!center)
		return JS_EXCEPTION;

	Vector2* size = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_rl_vector2_class_id);

	if (!size)
		return JS_EXCEPTION;

	Color* color = (Color*)JS_GetOpaque2(ctx, argv[2], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawPlane(*center, *size, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_ray(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Ray* ray = (Ray*)JS_GetOpaque2(ctx, argv[0], js_rl_ray_class_id);

	if (!ray)
		return JS_EXCEPTION;

	Color* color = (Color*)JS_GetOpaque2(ctx, argv[1], js_rl_color_class_id);

	if (!color)
		return JS_EXCEPTION;

	DrawRay(*ray, *color);

	return JS_UNDEFINED;
}

static JSValue rl_draw_grid(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	int slices;

	if (JS_ToInt32(ctx, &slices, argv[0]))
		return JS_EXCEPTION;
	
	double spacing;

	if (JS_ToFloat64(ctx, &spacing, argv[1]))
		return JS_EXCEPTION;

	DrawGrid(slices, spacing);

	return JS_UNDEFINED;
}

static JSValue rl_draw_gizmo(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
	Vector3* position = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_rl_vector3_class_id);

	if (!position)
		return JS_EXCEPTION;

	DrawGizmo(*position);

	return JS_UNDEFINED;
}

#pragma endregion

// function entries
static const JSCFunctionListEntry js_rl_funcs[] = {
	// module: core
	#pragma region Window-related functions

	JS_CFUNC_DEF("initWindow", 3, rl_init_window),
	JS_CFUNC_DEF("windowShouldClose", 1, rl_window_should_close),
	JS_CFUNC_DEF("closeWindow", 0, rl_close_window),
	JS_CFUNC_DEF("isWindowReady", 0, rl_is_window_ready),
	JS_CFUNC_DEF("isWindowMinimized", 0, rl_is_window_minimized),
	JS_CFUNC_DEF("isWindowResized", 0, rl_is_window_resized),
	JS_CFUNC_DEF("isWindowHidden", 0, rl_is_window_hidden),
	JS_CFUNC_DEF("toggleFullscreen", 0, rl_toggle_fullscreen),
	JS_CFUNC_DEF("unhideWindow", 0, rl_unhide_window),
	JS_CFUNC_DEF("hideWindow", 0, rl_hide_window),
	JS_CFUNC_DEF("setWindowIcon", 1, rl_set_window_icon),
	JS_CFUNC_DEF("setWindowTitle", 1, rl_set_window_title),
	JS_CFUNC_DEF("setWindowPosition", 2, rl_set_window_position),
	JS_CFUNC_DEF("setWindowMonitor", 1, rl_set_window_monitor),
	JS_CFUNC_DEF("setWindowMinSize", 2, rl_set_window_min_size),
	JS_CFUNC_DEF("setWindowSize", 2, rl_set_window_size),
	JS_CFUNC_DEF("getScreenWidth", 0, rl_get_screen_width),
	JS_CFUNC_DEF("getScreenHeight", 0, rl_get_screen_height),
	JS_CFUNC_DEF("getMonitorCount", 0, rl_get_monitor_count),
	JS_CFUNC_DEF("getMonitorWidth", 1, rl_get_monitor_width),
	JS_CFUNC_DEF("getMonitorHeight", 1, rl_get_monitor_height),
	JS_CFUNC_DEF("getMonitorPhysicalWidth", 1, rl_get_monitor_physical_width),
	JS_CFUNC_DEF("getMonitorPhysicalHeight", 1, rl_get_monitor_physical_height),
	JS_CFUNC_DEF("getMonitorName", 1, rl_get_monitor_name),
	JS_CFUNC_DEF("getClipboardText", 0, rl_get_clipboard_text),
	JS_CFUNC_DEF("setClipboardText", 1, rl_set_clipboard_text),

	#pragma endregion
	#pragma region Cursor-related functions

	JS_CFUNC_DEF("showCursor", 0, rl_show_cursor),
	JS_CFUNC_DEF("hideCursor", 0, rl_hide_cursor),
	JS_CFUNC_DEF("isCursorHidden", 0, rl_is_cursor_hidden),
	JS_CFUNC_DEF("enableHidden", 0, rl_enable_cursor),
	JS_CFUNC_DEF("disableHidden", 0, rl_disable_cursor),

	#pragma endregion
	#pragma region Drawing-related functions

	JS_CFUNC_DEF("clearBackground", 1, rl_clear_background),
	JS_CFUNC_DEF("beginDrawing", 0, rl_begin_drawing),
	JS_CFUNC_DEF("endDrawing", 0, rl_end_drawing),
	JS_CFUNC_DEF("beginMode2D", 1, rl_begin_mode_2d),
	JS_CFUNC_DEF("endMode2D", 0, rl_end_mode_2d),
	JS_CFUNC_DEF("beginMode3D", 1, rl_begin_mode_3d),
	JS_CFUNC_DEF("endMode3D", 0, rl_end_mode_3d),
	JS_CFUNC_DEF("beginTextureMode", 1, rl_begin_texture_mode),
	JS_CFUNC_DEF("endTextureMode", 0, rl_end_texture_mode),

	#pragma endregion
	#pragma region Screen-space-related functions

	JS_CFUNC_DEF("getMouseRay", 2, rl_get_mouse_ray),
	JS_CFUNC_DEF("getWorldToScreen", 2, rl_get_world_to_screen),
	JS_CFUNC_DEF("getCameraMatrix", 1, rl_get_camera_matrix),

	#pragma endregion
	#pragma region Timing-related functions

	JS_CFUNC_DEF("setTargetFps", 1, rl_set_target_fps),
	JS_CFUNC_DEF("getFps", 0, rl_get_fps),
	JS_CFUNC_DEF("getFrameTime", 0, rl_get_frame_time),
	JS_CFUNC_DEF("getTime", 0, rl_get_time),

	#pragma endregion
	#pragma region Color-related functions

	JS_CFUNC_DEF("colorToInt", 1, rl_color_to_int),
	JS_CFUNC_DEF("colorNormalize", 1, rl_color_normalize),
	JS_CFUNC_DEF("colorToHSV", 1, rl_color_to_hsv),
	JS_CFUNC_DEF("colorFromHSV", 1, rl_color_from_hsv),
	JS_CFUNC_DEF("getColor", 1, rl_get_color),
	JS_CFUNC_DEF("fade", 2, rl_fade),

	#pragma endregion
	#pragma region Misc. functions

	JS_CFUNC_DEF("setConfigFlags", 1, rl_set_config_flags),
	JS_CFUNC_DEF("setTraceLogLevel", 1, rl_set_trace_log_level),
	JS_CFUNC_DEF("setTraceLogExit", 1, rl_set_trace_log_exit),
	JS_CFUNC_DEF("takeScreenshot", 1, rl_take_screenshot),
	JS_CFUNC_DEF("getRandomValue", 2, rl_get_random_value),
	JS_CFUNC_DEF("openURL", 1, rl_open_url),

	#pragma endregion
	#pragma region Files management functions

	JS_CFUNC_DEF("fileExists", 1, rl_file_exists),
	JS_CFUNC_DEF("isFileExtension", 2, rl_is_file_extension),
	JS_CFUNC_DEF("getExtension", 1, rl_get_extension),
	JS_CFUNC_DEF("getFileName", 1, rl_get_file_name),
	JS_CFUNC_DEF("getFileNameWithoutExt", 1, rl_get_file_name_without_extension),
	JS_CFUNC_DEF("getDirectoryPath", 1, rl_get_directory_path),
	JS_CFUNC_DEF("getWorkingDirectory", 0, rl_get_working_directory),
	JS_CFUNC_DEF("getDirectoryFiles", 1, rl_get_directory_files),
	JS_CFUNC_DEF("changeDirectory", 1, rl_change_directory),
	JS_CFUNC_DEF("isFileDropped", 0, rl_is_file_dropped),
	JS_CFUNC_DEF("getDroppedFiles", 0, rl_get_dropped_files),
	JS_CFUNC_DEF("getFileModTime", 1, rl_get_file_mod_time),

	#pragma endregion
	#pragma region Persistent storage management

	JS_CFUNC_DEF("storageSaveValue", 2, rl_storage_save_value),
	JS_CFUNC_DEF("storageLoadValue", 1, rl_storage_load_value),

	#pragma endregion
	#pragma region Input-related functions: keyboard

	JS_CFUNC_DEF("isKeyPressed", 1, rl_is_key_pressed),
	JS_CFUNC_DEF("isKeyDown", 1, rl_is_key_down),
	JS_CFUNC_DEF("isKeyReleased", 1, rl_is_key_released),
	JS_CFUNC_DEF("isKeyUp", 1, rl_is_key_up),
	JS_CFUNC_DEF("getKeyPressed", 0, rl_get_key_pressed),
	JS_CFUNC_DEF("setExitKey", 1, rl_set_exit_key),

	#pragma endregion
	#pragma region Input-related functions: gamepads

	JS_CFUNC_DEF("isGamepadAvailable", 1, rl_is_gamepad_available),
	JS_CFUNC_DEF("isGamepadName", 2, rl_is_gamepad_name),
	JS_CFUNC_DEF("getGamepadName", 1, rl_get_gamepad_name),
	JS_CFUNC_DEF("isGamepadButtonPressed", 2, rl_is_gamepad_button_pressed),
	JS_CFUNC_DEF("isGamepadButtonDown", 2, rl_is_gamepad_button_down),
	JS_CFUNC_DEF("isGamepadButtonReleased", 2, rl_is_gamepad_button_released),
	JS_CFUNC_DEF("isGamepadButtonUp", 2, rl_is_gamepad_button_up),
	JS_CFUNC_DEF("getGamepadButtonPressed", 1, rl_get_gamepad_button_pressed),
	JS_CFUNC_DEF("getGamepadAxisCount", 1, rl_get_gamepad_axis_count),
	JS_CFUNC_DEF("getGamepadAxisMovement", 2, rl_get_gamepad_axis_movement),

	#pragma endregion
	#pragma region Input-related functions: mouse

	JS_CFUNC_DEF("isMouseButtonPressed", 1, rl_is_mouse_button_pressed),
	JS_CFUNC_DEF("isMouseButtonDown", 1, rl_is_mouse_button_down),
	JS_CFUNC_DEF("IsMouseButtonReleased", 1, rl_is_mouse_button_released),
	JS_CFUNC_DEF("isMouseButtonUp", 1, rl_is_mouse_button_up),
	JS_CFUNC_DEF("getMouseX", 0, rl_get_mouse_x),
	JS_CFUNC_DEF("getMouseY", 0, rl_get_mouse_y),
	JS_CFUNC_DEF("getMousePosition", 0, rl_get_mouse_position),
	JS_CFUNC_DEF("setMousePosition", 2, rl_set_mouse_position),
	JS_CFUNC_DEF("setMouseOffset", 2, rl_set_mouse_offset),
	JS_CFUNC_DEF("setMouseScale", 2, rl_set_mouse_scale),
	JS_CFUNC_DEF("getMouseWheelMove", 2, rl_get_mouse_wheel_move),

	#pragma endregion
	#pragma region Input-related functions: touch

	JS_CFUNC_DEF("getTouchX", 0, rl_get_touch_x),
	JS_CFUNC_DEF("getTouchY", 0, rl_get_touch_y),
	JS_CFUNC_DEF("getTouchPosition", 1, rl_get_touch_position),

	#pragma endregion
	#pragma region Gestures and Touch Handling Functions

	JS_CFUNC_DEF("setGesturesEnabled", 1, rl_set_gestures_enabled),
	JS_CFUNC_DEF("isGestureDetected", 1, rl_is_gesture_detected),
	JS_CFUNC_DEF("getGestureDetected", 0, rl_get_gesture_detected),
	JS_CFUNC_DEF("getTouchPointsCount", 0, rl_get_touch_points_count),
	JS_CFUNC_DEF("getGestureHoldDuration", 0, rl_get_gesture_hold_duration),
	JS_CFUNC_DEF("getGestureDragVector", 0, rl_get_gesture_drag_vector),
	JS_CFUNC_DEF("getGestureDragAngle", 0, rl_get_gesture_drag_angle),
	JS_CFUNC_DEF("getGesturePinchVector", 0, rl_get_gesture_pinch_vector),
	JS_CFUNC_DEF("getGesturePinchAngle", 0, rl_get_gesture_pinch_angle),

	#pragma endregion
	#pragma region Camera System Functions

	JS_CFUNC_DEF("setCameraMode", 2, rl_set_camera_mode),
	JS_CFUNC_DEF("updateCamera", 1, rl_update_camera),
	JS_CFUNC_DEF("setCameraPanControl", 1, rl_set_camera_pan_control),
	JS_CFUNC_DEF("setCameraAltControl", 1, rl_set_camera_alt_control),
	JS_CFUNC_DEF("setCameraSmoothZoomControl", 1, rl_set_camera_smooth_zoom_control),
	JS_CFUNC_DEF("setCameraMoveControls", 6, rl_set_camera_move_controls),

	#pragma endregion

	// module: shapes
	#pragma region Basic shapes drawing functions

	JS_CFUNC_DEF("drawPixel", 3, rl_draw_pixel),
	JS_CFUNC_DEF("drawPixelV", 2, rl_draw_pixel_v),
	JS_CFUNC_DEF("drawLine", 5, rl_draw_line),
	JS_CFUNC_DEF("drawLineV", 3, rl_draw_line_v),
	JS_CFUNC_DEF("drawLineEx", 4, rl_draw_line_ex),
	JS_CFUNC_DEF("drawLineBezier", 4, rl_draw_line_bezier),
	JS_CFUNC_DEF("drawLineStrip", 2, rl_draw_line_strip),

	JS_CFUNC_DEF("drawCircle", 4, rl_draw_circle),
	JS_CFUNC_DEF("drawCircleLines", 4, rl_draw_circle_lines),
	JS_CFUNC_DEF("drawCircleSector", 6, rl_draw_circle_sector),
	JS_CFUNC_DEF("drawCircleSectorLines", 6, rl_draw_circle_sector_lines),
	JS_CFUNC_DEF("drawCircleGradient", 5, rl_draw_circle_gradient),
	JS_CFUNC_DEF("drawCircleV", 4, rl_draw_circle_v),
	JS_CFUNC_DEF("drawRing", 7, rl_draw_ring),
	JS_CFUNC_DEF("drawRingLines", 7, rl_draw_ring_lines),
	JS_CFUNC_DEF("drawRectangle", 5, rl_draw_rectangle),
	JS_CFUNC_DEF("drawRectangleV", 3, rl_draw_rectangle_v),
	JS_CFUNC_DEF("drawRectangleRec", 2, rl_draw_rectangle_rec),
	JS_CFUNC_DEF("drawRectanglePro", 4, rl_draw_rectangle_pro),
	JS_CFUNC_DEF("drawRectangleGradientV", 6, rl_draw_rectangle_gradient_v),
	JS_CFUNC_DEF("drawRectangleGradientH", 6, rl_draw_rectangle_gradient_h),
	JS_CFUNC_DEF("drawRectangleGradientEx", 5, rl_draw_rectangle_gradient_ex),
	JS_CFUNC_DEF("drawRectangleLines", 5, rl_draw_rectangle_lines),
	JS_CFUNC_DEF("drawRectangleLinesEx", 3, rl_draw_rectangle_lines_ex),
	JS_CFUNC_DEF("drawRectangleRounded", 4, rl_draw_rectangle_rounded),
	JS_CFUNC_DEF("drawRectangleRoundedLines", 5, rl_draw_rectangle_rounded_lines),
	JS_CFUNC_DEF("drawTriangle", 4, rl_draw_triangle),
	JS_CFUNC_DEF("drawTriangleLines", 4, rl_draw_triangle_lines),
	JS_CFUNC_DEF("drawTriangleFan", 2, rl_draw_triangle_fan),
	JS_CFUNC_DEF("drawPoly", 5, rl_draw_poly),
	JS_CFUNC_DEF("setShapesTexture", 2, rl_set_shapes_texture),

	#pragma endregion
	#pragma region Basic shapes collision detection functions

	JS_CFUNC_DEF("checkCollisionRecs", 2, rl_check_collision_recs),
	JS_CFUNC_DEF("checkCollisionCircles", 4, rl_check_collision_circles),
	JS_CFUNC_DEF("checkCollisionCircleRec", 3, rl_check_collision_circle_rec),
	JS_CFUNC_DEF("getCollisionRec", 2, rl_get_collision_rec),
	JS_CFUNC_DEF("checkCollisionPointRec", 2, rl_check_collision_point_rec),
	JS_CFUNC_DEF("checkCollisionPointCircle", 2, rl_check_collision_point_circle),
	JS_CFUNC_DEF("checkCollisionPointTriangle", 4, rl_check_collision_point_triangle),

	#pragma endregion

	// module: textures
	#pragma region Image/Texture2D data loading/unloading/saving functions

	JS_CFUNC_DEF("loadImage", 1, rl_load_image),
	JS_CFUNC_DEF("loadImageEx", 3, rl_load_image_ex),
	JS_CFUNC_DEF("loadImagePro", 4, rl_load_image_pro),
	JS_CFUNC_DEF("loadImageRaw", 5, rl_load_image_raw),
	JS_CFUNC_DEF("exportImage", 2, rl_export_image),
	JS_CFUNC_DEF("exportImageAsCode", 2, rl_export_image_as_code),
	JS_CFUNC_DEF("loadTexture", 1, rl_load_texture),
	JS_CFUNC_DEF("loadTextureFromImage", 1, rl_load_texture_from_image),
	JS_CFUNC_DEF("loadTextureCubemap", 2, rl_load_texture_cubemap),
	JS_CFUNC_DEF("loadRenderTexture", 2, rl_load_render_texture),
	JS_CFUNC_DEF("unloadImage", 1, rl_unload_image),
	JS_CFUNC_DEF("unloadTexture", 1, rl_unload_texture),
	JS_CFUNC_DEF("unloadRenderTexture", 1, rl_unload_render_texture),
	JS_CFUNC_DEF("getImageData", 1, rl_get_image_data),
	JS_CFUNC_DEF("getImageDataNormalized", 1, rl_get_image_data_normalized),
	JS_CFUNC_DEF("getPixelDataSize", 3, rl_get_pixel_data_size),
	JS_CFUNC_DEF("getTextureData", 1, rl_get_texture_data),
	JS_CFUNC_DEF("getScreenData", 0, rl_get_screen_data),
	JS_CFUNC_DEF("updateTexture", 1, rl_update_texture),

	#pragma endregion
	#pragma region Image manipulation functions

	

	#pragma endregion
	#pragma region Image generation functions

	

	#pragma endregion
	#pragma region Texture2D configuration functions

	

	#pragma endregion
	#pragma region Texture2D drawing functions

	

	#pragma endregion

	// module: text
	#pragma region Font loading/unloading functions

	JS_CFUNC_DEF("getFontDefault", 0, rl_get_font_default),
	JS_CFUNC_DEF("loadFont", 1, rl_load_font),
	JS_CFUNC_DEF("loadFontEx", 1, rl_load_font_ex),
	JS_CFUNC_DEF("loadFontFromImage", 3, rl_load_font_from_image),
	JS_CFUNC_DEF("loadFontData", 5, rl_load_font_data),
	// JS_CFUNC_DEF("getImageFontAtlas", 5, rl_get_image_font_atlas),
	JS_CFUNC_DEF("unloadFont", 1, rl_unload_font),

	#pragma endregion
	#pragma region Text drawing functions

	JS_CFUNC_DEF("drawFps", 2, rl_draw_fps),
	JS_CFUNC_DEF("drawText", 5, rl_draw_text),
	JS_CFUNC_DEF("drawTextEx", 6, rl_draw_text_ex),
	JS_CFUNC_DEF("drawTextRec", 7, rl_draw_text_rec),
	JS_CFUNC_DEF("drawTextRecEx", 11, rl_draw_text_rec_ex),

	#pragma endregion
	#pragma region Text misc. functions

	JS_CFUNC_DEF("measureText", 2, rl_measure_text),
	JS_CFUNC_DEF("measureTextEx", 4, rl_measure_text_ex),
	JS_CFUNC_DEF("getGlyphIndex", 2, rl_get_glyph_index),

	#pragma endregion
	#pragma region Text strings management functions



	#pragma endregion

	// module: models
	#pragma region Basic geometric 3D shapes drawing functions

	JS_CFUNC_DEF("drawLine3d", 3, rl_draw_line_3d),
	JS_CFUNC_DEF("drawPoint3d", 2, rl_draw_point_3d),
	JS_CFUNC_DEF("drawCircle3d", 5, rl_draw_circle_3d),
	JS_CFUNC_DEF("drawCube", 5, rl_draw_cube),
	JS_CFUNC_DEF("drawCubeWires", 5, rl_draw_cube_wires),
	JS_CFUNC_DEF("drawCubeV", 3, rl_draw_cube_v),
	JS_CFUNC_DEF("drawCubeWiresV", 3, rl_draw_cube_wires_v),
	JS_CFUNC_DEF("drawCubeTexture", 6, rl_draw_cube_texture),
	JS_CFUNC_DEF("drawSphere", 3, rl_draw_sphere),
	JS_CFUNC_DEF("drawSphereEx", 5, rl_draw_sphere_ex),
	JS_CFUNC_DEF("drawSphereWires", 5, rl_draw_sphere_wires),
	JS_CFUNC_DEF("drawCylinder", 6, rl_draw_cylinder),
	JS_CFUNC_DEF("drawCylinderWires", 6, rl_draw_cylinder_wires),
	JS_CFUNC_DEF("drawPlane", 3, rl_draw_plane),
	JS_CFUNC_DEF("drawRay", 2, rl_draw_ray),
	JS_CFUNC_DEF("drawGrid", 2, rl_draw_grid),
	JS_CFUNC_DEF("drawGizmo", 1, rl_draw_gizmo),

	#pragma endregion
	#pragma region Model loading/unloading functions



	#pragma endregion
	#pragma region Mesh loading/unloading functions



	#pragma endregion
	#pragma region Material loading/unloading functions



	#pragma endregion
	#pragma region Model animations loading/unloading functions



	#pragma endregion
	#pragma region Mesh generation functions



	#pragma endregion
	#pragma region Mesh manipulation functions



	#pragma endregion
	#pragma region Model drawing functions



	#pragma endregion
	#pragma region Collision detection functions



	#pragma endregion

	// module: shaders
	#pragma region Shader loading/unloading functions



	#pragma endregion
	#pragma region Shader configuration functions



	#pragma endregion
	#pragma region Shading begin/end functions



	#pragma endregion
	#pragma region VR control functions



	#pragma endregion

	// module: audio
	#pragma region Audio device management functions



	#pragma endregion
	#pragma region Wave/Sound loading/unloading functions



	#pragma endregion
	#pragma region Wave/Sound management functions



	#pragma endregion
	#pragma region Music management functions



	#pragma endregion
	#pragma region AudioStream management functions



	#pragma endregion
};

// initialize as a QuickJS module

static int js_rl_init(JSContext* ctx, JSModuleDef* m)
{
	js_rl_init_classes(ctx, m);

	return JS_SetModuleExportList(ctx, m, js_rl_funcs, countof(js_rl_funcs));
}

JSModuleDef* js_init_module(JSContext* ctx, const char* module_name)
{
	JSModuleDef* m;
	m = JS_NewCModule(ctx, module_name, js_rl_init);
	
	if (!m)
		return NULL;
	
	JS_AddModuleExportList(ctx, m, js_rl_funcs, countof(js_rl_funcs));
	js_rl_init_module_classes(ctx, m);

	return m;
}
