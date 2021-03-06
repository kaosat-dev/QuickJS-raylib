import { Vector2, Color, Rectangle } from './qjs-raylib.so';

// Basic shapes drawing functions
export function drawPixel(posX: number, posY: number, color: Color): void;
export function drawPixelV(position: Vector2, color: Color): void;
export function drawLine(startPosX: number, startPosY: number, endPosX: number, endPostY: number, color: Color): void;
export function drawLineV(startPos: Vector2, endPos: Vector2, color: Color): void;
export function drawLineEx(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void;
export function drawLineBezier(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void;
export function drawLineStrip(points: Vector2[], color: Color): void;

export function drawCircle(centerX: number, centerY: number, radius: number, color: Color): void;
export function drawCircleLines(centerX: number, centerY: number, radius: number, color: Color): void;
export function drawCircleSector(center: Vector2, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
export function drawCircleSectorLines(center: Vector2, radius: number, startAngle: number, endAngle: number,segments: number, color: Color): void;
export function drawCircleGradient(centerX: number, centerY: number, radius: number, color1: Color, color2: Color): void;
export function drawCircleV(center: Vector2, radius: number, color: Color): void;
export function drawRing(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
export function drawRingLines(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
export function drawRectangle(posX: number, poxY: number, width: number, height: number, color: Color): void;
export function drawRectangleV(position: Vector2, size: Vector2, color: Color): void;
export function drawRectangleRec(rec: Rectangle, color: Color): void;
export function drawRectanglePro(rec: Rectangle, origin: Vector2, rotation: number, color: Color): void;
export function drawRectangleGradientV(posX: number, poxY: number, width: number, height: number, color1: Color, color2: Color): void;
export function drawRectangleGradientH(posX: number, poxY: number, width: number, height: number, color1: Color, color2: Color): void;
export function drawRectangleGradientEx(rec: Rectangle, color1: Color, color2: Color, color3: Color, color4: Color): void;
export function drawRectangleLines(posX: number, poxY: number, width: number, height: number, color: Color): void;
export function drawRectangleLinesEx(rect: Rectangle, lineThick: number, color: Color): void;
export function drawRectangleRounded(rec: Rectangle, roundness: number, segments: number, color: Color): void;
export function drawRectangleRoundedLines(rec: Rectangle, roundness: number, segments: number, lineThick: number, color: Color): void;
export function drawTriangle(v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
export function drawTriangleLines(points: Vector2[], color: Color): void;
export function drawTriangleFan(center: Vector2, sides: number, radius: number, rotation: number, color: Color): void;

// Basic shapes collision detection functions
export function checkCollisionRecs(rec1: Rectangle, rec2: Rectangle): boolean;
export function checkCollisionCircles(center1: Vector2, radius1: number, center2: Vector2, radius2: number): boolean;
export function checkCollisionCircleRec(center: Vector2, radius: number, rec: Rectangle): boolean;
export function getCollisionRec(rec1: Rectangle, rec2: Rectangle): Rectangle;
export function checkCollisionPointRec(point: Vector2, rec: Rectangle): boolean;
export function checkCollisionPointCircle(point: Vector2, center: Vector2, radius: number): boolean;
export function checkCollisionPointTriangle(point: Vector2, p1: Vector2, p2: Vector2, p3: Vector2): boolean;
