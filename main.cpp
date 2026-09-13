// ============================================================
//  Celestial Dreams - OpenGL Project
// ============================================================

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265f

// ==================== GLOBAL VARIABLES ====================

float gMouseWX = 0.0f;
float gMouseWY = 0.0f;

// variables
float fanSpin = 0.0f;
float clockTime = 0.0f;
float mousePosX = -130.0f;
bool lampLit = false;
float lampGlow = 0.0f;
bool boyAsleep = false;
bool dreamActive = false;
float sleepCount = 0.0f;
float zoomLevel = 1.0f;
bool spaceMode = false;
bool treehouseMode = false;
float treehouseTimer = 0.0f;
float fanSpeed = 15.0f;
float dreamCloudX = 0.0f;
float dreamCloudY = 0.0f;
bool dreamPopped = false;

// space variables
float sX[300], sY[300];
bool starsReady = false;
float shipY = -130.0f;
float rocketBoost = 0.0f;
bool planetsPaused = false;
float mercuryOrbit = 0.0f;
float venusOrbit = 0.0f;
float earthOrbit = 0.0f;
float wallTimer = 0.0f;
bool wallMode = false;
float floatY = 0.0f;
float tiltAngle = 0.0f;
int highlightedPlanet = -1;
float astroFollowY = 0.0f;

// journey variables
bool journeyActive = false;
bool jupiterLanding = false;
float journeyTimer = 0.0f;
float jupiterSize = 5.0f;
float rocketJourneyX = 0.0f;
float marsPhase = 0;
float marsTimer = 0.0f;
float marsPhaseTimer = 0.0f;
float landRocketY = 90.0f;
float girlWalkX = 8.0f;
float alienAppear = 0.0f;
float escapeRocketY = -45.0f;
float warningAlpha = 0.0f;
bool starsInitDone = false;
float alienDodgeX[5] = {0, 0, 0, 0, 0};
float alienDodgeY[5] = {0, 0, 0, 0, 0};
float laserX = 0.0f;
float laserY = 0.0f;
float laserActive = 0.0f;
float astroAimAngle = 0.0f;

// wake up variables
bool wakeMode = false;
float wakeTimer = 0.0f;
float wakeHeadLift = 0.0f;
float wakeHeadTurn = 0.0f;
float wakeSpeed = 1.0f;

bool thankyouMode = false;
float thankyouTimer = 0.0f;

const float DT = 1.0f / 60.0f;

// ==================== HELPER FUNCTIONS ====================

float clampFloat(float v, float lo, float hi) {
    if (v < lo) {
        return lo;
    }
    if (v > hi) {
        return hi;
    }
    return v;
}

float smoothStep(float t) {
    t = clampFloat(t, 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

void drawRect(float x, float y, float w, float h, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void drawCircle(float cx, float cy, float rad, int segs, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segs; i++) {
        float a = i * 2.0f * PI / segs;
        glVertex2f(cx + rad * cosf(a), cy + rad * sinf(a));
    }
    glEnd();
}

void drawLabel(float x, float y, const char *s, void *font = GLUT_BITMAP_HELVETICA_12) {
    glRasterPos2f(x, y);
    while (*s) {
        glutBitmapCharacter(font, *s++);
    }
}

// ============================================================
//  DEV2 - SHARED: ROCKET DRAWING
// ============================================================
void drawRocket(float x, float y, float flameFlicker, bool showFlame, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1.0f);

    if (showFlame) {
        float fl = clampFloat(flameFlicker, 0.0f, 1.0f);
        glColor3f(1.0f, 0.42f + fl * 0.18f, 0.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(-5, 0);
        glVertex2f(5, 0);
        glVertex2f(0, -18.0f - fl * 10.0f);
        glEnd();
        glColor3f(1.0f, 1.0f, 0.28f);
        glBegin(GL_TRIANGLES);
        glVertex2f(-3, 0);
        glVertex2f(3, 0);
        glVertex2f(0, -10.0f - fl * 6.0f);
        glEnd();
    }

    drawRect(-8, 0, 16, 45, 0.92f, 0.92f, 0.95f);
    drawRect(-4, 0, 8, 45, 0.97f, 0.97f, 1.0f);

    glColor3f(0.10f, 0.30f, 0.75f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-8, 45);
    glVertex2f(8, 45);
    glVertex2f(0, 60);
    glEnd();
    glColor3f(0.15f, 0.40f, 0.85f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-4, 45);
    glVertex2f(4, 45);
    glVertex2f(0, 58);
    glEnd();

    glColor3f(0.08f, 0.25f, 0.65f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-8, 5);
    glVertex2f(-16, -5);
    glVertex2f(-8, 15);
    glVertex2f(8, 5);
    glVertex2f(16, -5);
    glVertex2f(8, 15);
    glEnd();
    glColor3f(0.38f, 0.38f, 0.42f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-8, 8);
    glVertex2f(-12, -2);
    glVertex2f(8, 8);
    glVertex2f(12, -2);
    glEnd();

    drawCircle(0, 32, 4.5f, 18, 0.38f, 0.38f, 0.42f);
    drawCircle(0, 32, 3.5f, 16, 0.08f, 0.18f, 0.50f);
    drawCircle(-1, 33, 1.0f, 10, 0.55f, 0.75f, 1.0f);
    drawCircle(0, 18, 4.5f, 18, 0.38f, 0.38f, 0.42f);
    drawCircle(0, 18, 3.5f, 16, 0.08f, 0.18f, 0.50f);
    drawCircle(-1, 19, 1.0f, 10, 0.55f, 0.75f, 1.0f);

    drawRect(-8, 25, 16, 2, 0.08f, 0.25f, 0.65f);
    drawRect(-8, 11, 16, 2, 0.08f, 0.25f, 0.65f);

    glPopMatrix();
}

// ============================================================
//  DEV2 - SHARED: ASTRONAUT DRAWING
// ============================================================
void drawAstronaut(float x, float y, float armSwing, float legSwing, float tilt, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(tilt, 0, 0, 1);
    glScalef(scale, scale, 1.0f);

    glPushMatrix();
    glTranslatef(-5, -30, 0);
    glRotatef(legSwing, 0, 0, 1);
    drawRect(-6, -18, 10, 18, 0.90f, 0.90f, 0.93f);
    drawRect(-4, -16, 6, 14, 0.95f, 0.95f, 0.98f);
    drawCircle(-1, -18, 4.0f, 14, 0.38f, 0.38f, 0.42f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, -30, 0);
    glRotatef(-legSwing, 0, 0, 1);
    drawRect(-4, -18, 10, 18, 0.90f, 0.90f, 0.93f);
    drawRect(-2, -16, 6, 14, 0.95f, 0.95f, 0.98f);
    drawCircle(1, -18, 4.0f, 14, 0.38f, 0.38f, 0.42f);
    glPopMatrix();

    drawRect(-10, -30, 20, 38, 0.90f, 0.90f, 0.93f);
    drawRect(-7, -28, 14, 34, 0.95f, 0.95f, 0.98f);

    drawRect(-14, -25, 28, 32, 0.55f, 0.55f, 0.58f);
    drawRect(-12, -22, 24, 26, 0.68f, 0.68f, 0.72f);
    drawRect(-6, -18, 12, 10, 0.38f, 0.38f, 0.42f);

    drawRect(-6, -8, 12, 12, 0.65f, 0.68f, 0.72f);
    drawCircle(-3, -2, 1.5f, 10, 1.0f, 0.18f, 0.18f);
    drawCircle(3, -2, 1.5f, 10, 0.18f, 0.75f, 0.18f);
    drawRect(-4, -6, 8, 3, 0.08f, 0.15f, 0.45f);

    glPushMatrix();
    glTranslatef(-10, 0, 0);
    glRotatef(20 + armSwing * 15, 0, 0, 1);
    drawRect(-10, -5, 15, 12, 0.90f, 0.90f, 0.93f);
    drawRect(-8, -3, 11, 8, 0.95f, 0.95f, 0.98f);
    drawRect(-12, -7, 10, 8, 0.65f, 0.68f, 0.72f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, 0);
    glRotatef(-20 - armSwing * 15, 0, 0, 1);
    drawRect(0, -5, 15, 12, 0.90f, 0.90f, 0.93f);
    drawRect(2, -3, 11, 8, 0.95f, 0.95f, 0.98f);
    drawRect(2, -7, 10, 8, 0.65f, 0.68f, 0.72f);
    glPopMatrix();

    drawCircle(0, 18, 14, 28, 1.0f, 1.0f, 1.0f);
    drawCircle(0, 18, 10, 28, 0.05f, 0.10f, 0.25f);
    glColor3f(0.75f, 0.55f, 0.08f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 18);
    for (int i = 0; i <= 14; i++) {
        float t = i * PI / 14;
        glVertex2f(10.0f * cosf(t), 18 + 10.0f * sinf(t));
    }
    glEnd();
    drawCircle(-4, 22, 2.5f, 14, 1.0f, 1.0f, 1.0f);
    drawCircle(-2, 20, 1.0f, 10, 0.88f, 0.88f, 0.90f);
    drawCircle(-10, 26, 2.0f, 14, 1.0f, 1.0f, 0.45f);

    glPopMatrix();
}

// ============================================================
//  DEV1 - BEDROOM OBJECT FUNCTIONS
// ============================================================

void drawBedroomWall() {
    float dim = smoothStep(sleepCount / 7.0f);
    if (lampGlow > 0.5f) {
        dim = 0.2f;
    }
    glBegin(GL_QUADS);
    glColor3f(0.30f * (1 - dim * 0.3f), 0.55f * (1 - dim * 0.3f), 0.30f * (1 - dim * 0.3f));
    glVertex2f(-100, 100);
    glVertex2f(100, 100);
    glColor3f(0.25f * (1 - dim * 0.3f), 0.48f * (1 - dim * 0.3f), 0.25f * (1 - dim * 0.3f));
    glVertex2f(100, 40);
    glVertex2f(-100, 40);
    glColor3f(0.18f * (1 - dim * 0.3f), 0.35f * (1 - dim * 0.3f), 0.18f * (1 - dim * 0.3f));
    glVertex2f(-100, 40);
    glVertex2f(100, 40);
    glColor3f(0.10f * (1 - dim * 0.3f), 0.22f * (1 - dim * 0.3f), 0.10f * (1 - dim * 0.3f));
    glVertex2f(100, -20);
    glVertex2f(-100, -20);
    glEnd();
}

void drawBedroomFloor() {
    float dim = smoothStep(sleepCount / 7.0f);
    if (lampGlow > 0.5f) {
        dim = 0.2f;
    }
    glBegin(GL_QUADS);
    glColor3f(0.45f * (1 - dim * 0.5f), 0.45f * (1 - dim * 0.5f), 0.48f * (1 - dim * 0.5f));
    glVertex2f(-100, -20);
    glVertex2f(100, -20);
    glColor3f(0.30f * (1 - dim * 0.5f), 0.30f * (1 - dim * 0.5f), 0.32f * (1 - dim * 0.5f));
    glVertex2f(100, -100);
    glVertex2f(-100, -100);
    glEnd();
}

void drawBedroomWindow() {
    drawRect(-90, 45, 30, 40, 0.22f, 0.12f, 0.06f);
    drawRect(-87, 48, 24, 34, 0.0f, 0.0f, 0.15f);
    drawCircle(-80, 70, 0.5f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(-72, 65, 0.4f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(-76, 75, 0.5f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(-68, 60, 0.4f, 8, 1.0f, 1.0f, 1.0f);
}

void drawWindowMoon() {
    drawCircle(-78, 72, 5, 20, 0.90f, 0.88f, 0.60f);
    glColor3f(0.22f, 0.12f, 0.06f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(-75, 48);
    glVertex2f(-75, 82);
    glVertex2f(-87, 65);
    glVertex2f(-63, 65);
    glEnd();
}

void drawWindowCurtains() {
    drawRect(-92, 43, 6, 44, 0.60f, 0.10f, 0.15f);
    drawRect(-61, 43, 6, 44, 0.60f, 0.10f, 0.15f);
}

void drawPictureFrame() {
    drawRect(60, 55, 20, 25, 0.18f, 0.10f, 0.05f);
    drawRect(62, 57, 16, 21, 0.80f, 0.85f, 0.90f);
    drawRect(68, 60, 4, 12, 0.90f, 0.90f, 0.93f);
    glColor3f(0.15f, 0.35f, 0.75f);
    glBegin(GL_TRIANGLES);
    glVertex2f(68, 72);
    glVertex2f(72, 72);
    glVertex2f(70, 76);
    glEnd();
}

void drawCeilingFan() {
    drawRect(28, 80, 2, 20, 0.18f, 0.18f, 0.20f);
    glPushMatrix();
    glTranslatef(29, 80, 0);
    glRotatef(fanSpin, 0, 0, 1);
    drawCircle(0, 0, 4, 18, 0.28f, 0.28f, 0.30f);
    drawRect(-24, -2, 20, 4, 0.40f, 0.22f, 0.12f);
    drawRect(4, -2, 20, 4, 0.40f, 0.22f, 0.12f);
    glPopMatrix();
}

void drawBoyHead() {
    drawCircle(-16, 20, 11, 28, 0.25f, 0.15f, 0.08f);
    drawCircle(-23, 12, 9, 28, 0.25f, 0.15f, 0.08f);
    drawCircle(-9, 12, 9, 28, 0.25f, 0.15f, 0.08f);
    drawRect(-30, -2, 26, 15, 0.25f, 0.15f, 0.08f);
    drawCircle(-16, 5, 3.2f, 18, 0.90f, 0.75f, 0.55f);
    drawCircle(-16, 16, 10.0f, 28, 0.90f, 0.75f, 0.55f);

    if (boyAsleep) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_STRIP);
        glVertex2f(-20.5f, 15.5f);
        glVertex2f(-19.0f, 14.5f);
        glVertex2f(-17.5f, 15.5f);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(-14.5f, 15.5f);
        glVertex2f(-13.0f, 14.5f);
        glVertex2f(-11.5f, 15.5f);
        glEnd();
        drawCircle(-16, 11, 1.4f, 10, 0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(-21, 18);
        glVertex2f(-17, 19);
        glVertex2f(-15, 19);
        glVertex2f(-11, 18);
        glEnd();
    } else {
        float drowsy = smoothStep(sleepCount / 7.0f);
        float eyeFollowX = clampFloat(gMouseWX * 0.008f, -1.5f, 1.5f);
        float eyeFollowY = clampFloat(gMouseWY * 0.005f, -0.8f, 0.8f);
        drawCircle(-19, 17, 2.0f, 14, 1.0f, 1.0f, 1.0f);
        drawCircle(-13, 17, 2.0f, 14, 1.0f, 1.0f, 1.0f);
        float eyeDip = drowsy * 1.5f;
        drawCircle(-19 + eyeFollowX, 16.5f - eyeDip * 0.5f + eyeFollowY, 1.0f, 10, 0.08f, 0.08f, 0.15f);
        drawCircle(-13 + eyeFollowX, 16.5f - eyeDip * 0.5f + eyeFollowY, 1.0f, 10, 0.08f, 0.08f, 0.15f);
        if (drowsy > 0.05f) {
            glColor3f(0.85f, 0.65f, 0.45f);
            glBegin(GL_QUADS);
            glVertex2f(-21.5f, 19);
            glVertex2f(-16.5f, 19);
            glVertex2f(-16.5f, 19 - drowsy * 2.8f);
            glVertex2f(-21.5f, 19 - drowsy * 2.8f);
            glVertex2f(-15.5f, 19);
            glVertex2f(-10.5f, 19);
            glVertex2f(-10.5f, 19 - drowsy * 2.8f);
            glVertex2f(-15.5f, 19 - drowsy * 2.8f);
            glEnd();
        }
        glColor3f(0.20f, 0.12f, 0.06f);
        glLineWidth(2.5f);
        glBegin(GL_LINES);
        glVertex2f(-21, 20.5f - drowsy);
        glVertex2f(-17, 21.5f - drowsy * 1.5f);
        glVertex2f(-15, 21.5f - drowsy * 1.5f);
        glVertex2f(-11, 20.5f - drowsy);
        glEnd();
        if (drowsy > 0.6f) {
            drawCircle(-16, 11.5f, 0.8f + drowsy * 0.6f, 10, 0.08f, 0.0f, 0.0f);
        } else {
            glBegin(GL_LINE_STRIP);
            glVertex2f(-18, 11.5f);
            glVertex2f(-16, 11.0f);
            glVertex2f(-14, 11.5f);
            glEnd();
        }
    }
}

void drawBoyBody() {
    drawRect(-30, -45, 24, 24, 0.30f, 0.15f, 0.06f);
    drawRect(-28, -60, 3, 15, 0.18f, 0.08f, 0.02f);
    drawRect(-9, -60, 3, 15, 0.18f, 0.08f, 0.02f);
    drawRect(-26, -55, 7, 24, 0.85f, 0.70f, 0.55f);
    drawRect(-15, -55, 7, 24, 0.85f, 0.70f, 0.55f);
    drawRect(-28, -60, 9, 5, 0.15f, 0.25f, 0.50f);
    drawRect(-16, -60, 9, 5, 0.15f, 0.25f, 0.50f);
    glColor3f(0.15f, 0.35f, 0.70f);
    glBegin(GL_POLYGON);
    glVertex2f(-28, -28);
    glVertex2f(-24, 5);
    glVertex2f(-6, 5);
    glVertex2f(-2, -28);
    glEnd();
}

void drawBoyArms() {
    if (boyAsleep) {
        glPushMatrix();
        glTranslatef(-24, -10, 0);
        glRotatef(15, 0, 0, 1);
        drawRect(-3, -14, 6, 18, 0.15f, 0.35f, 0.70f);
        drawCircle(0, -14, 3, 10, 0.90f, 0.75f, 0.55f);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-8, -10, 0);
        glRotatef(-15, 0, 0, 1);
        drawRect(-3, -14, 6, 18, 0.15f, 0.35f, 0.70f);
        drawCircle(0, -14, 3, 10, 0.90f, 0.75f, 0.55f);
        glPopMatrix();
    } else {
        glPushMatrix();
        glTranslatef(-27, 0, 0);
        glRotatef(30, 0, 0, 1);
        drawRect(-3, -18, 6, 20, 0.15f, 0.35f, 0.70f);
        drawCircle(0, -18, 3, 10, 0.90f, 0.75f, 0.55f);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-7, 0, 0);
        glRotatef(-30, 0, 0, 1);
        drawRect(-3, -18, 6, 20, 0.15f, 0.35f, 0.70f);
        drawCircle(0, -18, 3, 10, 0.90f, 0.75f, 0.55f);
        glPopMatrix();
    }
}

void drawLamp() {
    float lampPulse = lampGlow * (sinf(sleepCount * 8.0f) * 0.1f + 0.9f);
    glPushMatrix();
    glTranslatef(22, -13, 0);
    drawRect(-62, -7, 20, 4, 0.12f, 0.12f, 0.14f);
    drawRect(-53, -3, 2, 18, 0.20f, 0.20f, 0.22f);
    glColor3f(0.10f, 0.30f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-67, 15);
    glVertex2f(-37, 15);
    glVertex2f(-44, 28);
    glVertex2f(-60, 28);
    glEnd();
    if (lampGlow > 0.1f) {
        drawCircle(-52, 18, 3, 18, 1.0f, 1.0f, 0.75f * lampPulse);
        drawCircle(-52, -5, 1.5f, 18, 1.0f, 1.0f, 0.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_TRIANGLES);
        glColor4f(0.8f, 0.9f, 1.0f, 0.55f * lampPulse);
        glVertex2f(-52, 15);
        glColor4f(0.8f, 0.9f, 1.0f, 0.0f);
        glVertex2f(-87, -15);
        glColor4f(0.8f, 0.9f, 1.0f, 0.0f);
        glVertex2f(-17, -15);
        glEnd();
        glDisable(GL_BLEND);
    } else {
        drawCircle(-52, -5, 1.5f, 18, 0.35f, 0.35f, 0.38f);
    }
    glPopMatrix();
}

void drawLampGlow() {
    glPushMatrix();
    glTranslatef(0, -20, 0);
    drawRect(-6, 0, 12, 8, 0.75f, 0.78f, 0.82f);
    drawRect(-5, 1, 10, 6, 0.08f, 0.10f, 0.18f);
    drawRect(-8, -2, 16, 2, 0.65f, 0.68f, 0.72f);
    if (lampGlow > 0.1f) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
        glColor4f(0.4f, 0.7f, 1.0f, 0.18f * lampGlow);
        glVertex2f(-5, 1);
        glVertex2f(5, 1);
        glColor4f(0.4f, 0.7f, 1.0f, 0.0f);
        glVertex2f(10, -10);
        glVertex2f(-10, -10);
        glEnd();
        glDisable(GL_BLEND);
    }
    glPopMatrix();
}

void drawPlant() {
}

void drawDesk() {
    drawRect(-42, -60, 4, 30, 0.25f, 0.12f, 0.04f);
    drawRect(28, -60, 4, 30, 0.25f, 0.12f, 0.04f);
    drawRect(-47, -30, 79, 10, 0.40f, 0.22f, 0.12f);
    drawRect(-47, -35, 79, 5, 0.25f, 0.12f, 0.04f);
}

void drawBooksDesk() {
    glPushMatrix();
    glTranslatef(12, -20, 0);
    drawRect(0, 0, 10, 3, 0.15f, 0.30f, 0.70f);
    drawRect(0, 3, 9, 3, 0.70f, 0.25f, 0.15f);
    drawRect(-1, 6, 10, 3, 0.10f, 0.55f, 0.25f);
    glPushMatrix();
    glTranslatef(-1, 9, 0);
    glRotatef(10, 0, 0, 1);
    drawRect(0, 0, 10, 2.5f, 0.75f, 0.65f, 0.10f);
    glPopMatrix();
    glPopMatrix();
}

void drawBookshelf() {
    drawRect(46, -20, 34, 55, 0.38f, 0.20f, 0.06f);
    drawRect(48, 20, 30, 2, 0.32f, 0.16f, 0.05f);
    drawRect(48, 0, 30, 2, 0.32f, 0.16f, 0.05f);
    drawRect(48, -18, 30, 2, 0.32f, 0.16f, 0.05f);
    drawRect(50, 22, 5, 12, 0.60f, 0.15f, 0.10f);
    drawRect(56, 22, 4, 10, 0.10f, 0.45f, 0.60f);
    drawRect(61, 22, 6, 11, 0.70f, 0.55f, 0.10f);
    drawRect(68, 22, 4, 9, 0.20f, 0.60f, 0.25f);
    drawRect(50, 2, 5, 10, 0.55f, 0.20f, 0.50f);
    drawRect(56, 2, 6, 12, 0.15f, 0.50f, 0.55f);
    drawRect(63, 2, 4, 8, 0.80f, 0.30f, 0.15f);
    drawRect(68, 2, 5, 11, 0.25f, 0.35f, 0.70f);
}

void drawTreePot() {
    glColor3f(0.50f, 0.25f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(52, 53);
    glVertex2f(72, 53);
    glVertex2f(68, 37);
    glVertex2f(56, 37);
    glEnd();
    drawRect(61, 53, 2, 14, 0.10f, 0.30f, 0.10f);
    drawCircle(62, 67, 9, 18, 0.10f, 0.50f, 0.12f);
    drawCircle(54, 62, 6, 16, 0.08f, 0.42f, 0.10f);
    drawCircle(70, 62, 6, 16, 0.08f, 0.42f, 0.10f);
}

void drawClock() {
    glPushMatrix();
    glTranslatef(-5, -12, 0);
    drawCircle(25, 0, 8, 28, 0.10f, 0.45f, 0.55f);
    drawCircle(25, 0, 7, 28, 0.95f, 0.95f, 1.0f);
    glPushMatrix();
    glTranslatef(25, 0, 0);
    glColor3f(0.10f, 0.45f, 0.55f);
    glLineWidth(2.0f);
    glPushMatrix();
    glRotatef(-clockTime * 12, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, 6);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glRotatef(-clockTime, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(4, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();
    glBegin(GL_TRIANGLES);
    glVertex2f(25, 0);
    glVertex2f(20, -8);
    glVertex2f(30, -8);
    glEnd();
    glPopMatrix();
}

void drawMouseAnimal() {
    drawCircle(mousePosX, -88, 3, 18, 0.50f, 0.25f, 0.10f);
    drawCircle(mousePosX + 3, -88, 1.8f, 16, 0.50f, 0.25f, 0.10f);
    drawCircle(mousePosX + 2, -86, 1, 10, 0.60f, 0.40f, 0.20f);
    glColor3f(0.35f, 0.35f, 0.38f);
    glBegin(GL_LINES);
    glVertex2f(mousePosX - 3, -88);
    glVertex2f(mousePosX - 8, -86);
    glEnd();
}

void drawDreamCloud() {
    if (dreamActive && !dreamPopped) {
        float bob = sinf(sleepCount * 3.0f) * 2.0f;
        float glow = (sinf(sleepCount * 4.0f) + 1.0f) * 0.2f;
        glPushMatrix();
        glTranslatef(dreamCloudX, bob + dreamCloudY, 0);
        if (sleepCount > 8.0f) {
            drawCircle(-5, 25, 1.5f, 18, 0.85f + glow, 0.90f + glow, 1.0f);
        }
        if (sleepCount > 8.5f) {
            drawCircle(0, 30, 2.5f, 18, 0.85f + glow, 0.90f + glow, 1.0f);
        }
        if (sleepCount > 9.0f) {
            drawCircle(5, 38, 3.5f, 18, 0.85f + glow, 0.90f + glow, 1.0f);
        }
        if (sleepCount > 9.5f) {
            drawCircle(12, 65, 12, 28, 0.85f + glow, 0.90f + glow, 1.0f);
            drawCircle(22, 68, 10, 28, 0.85f + glow, 0.90f + glow, 1.0f);
            drawCircle(2, 68, 10, 28, 0.85f + glow, 0.90f + glow, 1.0f);
            drawCircle(12, 74, 9, 28, 0.85f + glow, 0.90f + glow, 1.0f);
            glColor3f(0.15f, 0.35f, 0.75f);
            drawLabel(-2, 65, "Dreaming...", GLUT_BITMAP_HELVETICA_18);
        }
        glPopMatrix();
    }
}

// ==================== BEDROOM SCENE ====================

void drawBedroomScene() {
    drawBedroomWall();
    drawBedroomFloor();
    drawBedroomWindow();
    drawWindowMoon();
    drawWindowCurtains();
    drawPictureFrame();
    drawCeilingFan();

    glPushMatrix();
    if (boyAsleep) {
        glTranslatef(0, -8, 0);
    }
    drawBoyBody();
    drawBoyHead();
    glPopMatrix();

    drawDesk();

    glPushMatrix();
    if (boyAsleep) {
        glTranslatef(0, -8, 0);
    }
    drawBoyArms();
    glPopMatrix();

    drawLamp();
    drawLampGlow();
    drawBooksDesk();
    drawBookshelf();
    drawTreePot();
    drawClock();
    drawMouseAnimal();
    drawDreamCloud();

    glColor3f(0.4f, 0.4f, 0.4f);
    drawLabel(-95, -95, "Click lamp | Move mouse = boy eyes follow | F = fan speed", GLUT_BITMAP_HELVETICA_10);
}

// ============================================================
//  DEV2 - SCENE 1: DEEP SPACE - OBJECT FUNCTIONS
// ============================================================

void drawSpaceBackground() {
    glBegin(GL_QUADS);
    glColor3f(0.01f, 0.0f, 0.06f);
    glVertex2f(-100, -100);
    glVertex2f(100, -100);
    glColor3f(0.0f, 0.0f, 0.12f);
    glVertex2f(100, 100);
    glVertex2f(-100, 100);
    glEnd();
}

void drawSpaceStars() {
    if (!starsReady) {
        for (int i = 0; i < 300; i++) {
            sX[i] = (float)(rand() % 200) - 100.0f;
            sY[i] = (float)(rand() % 200) - 100.0f;
        }
        starsReady = true;
    }

    for (int i = 0; i < 300; i++) {
        float twk = (sinf(floatY * 0.3f + i) + 1.0f) * 0.5f;
        drawCircle(sX[i], sY[i], 0.3f + twk * 0.2f, 5, 0.7f + twk * 0.2f, 0.8f + twk * 0.2f, 0.95f + twk * 0.05f);
    }
}

void drawMeteors() {
    for (int i = 0; i < 5; i++) {
        float mx = fmodf((sX[i * 10] + floatY * (40.0f + i * 10.0f)), 250.0f) - 125.0f;
        float my = sY[i * 10];
        glColor3f(0.7f, 0.85f, 1.0f);
        glBegin(GL_LINES);
        glVertex2f(mx, my);
        glVertex2f(mx - 15.0f - i * 5.0f, my - 2.0f);
        glEnd();
        drawCircle(mx, my, 0.4f, 6, 1.0f, 1.0f, 1.0f);
    }
}

void drawSun() {
    drawCircle(-70, 0, 26, 38, 1.0f, 0.85f, 0.0f);
    drawCircle(-70, 0, 22, 48, 1.0f, 0.90f, 0.20f);
    drawCircle(-70, 0, 18, 48, 1.0f, 0.95f, 0.40f);
}

void drawMercury() {
    glPushMatrix();
    glTranslatef(-70, 0, 0);
    glRotatef(mercuryOrbit, 0, 0, 1);
    drawCircle(30, 0, 3, 18, 0.55f, 0.52f, 0.50f);
    drawCircle(30, 0, 1.5f, 16, 0.70f, 0.68f, 0.65f);
    glPopMatrix();
}

void drawVenus() {
    glPushMatrix();
    glTranslatef(-70, 0, 0);
    glRotatef(venusOrbit, 0, 0, 1);
    drawCircle(45, 0, 5, 18, 0.85f, 0.60f, 0.25f);
    drawCircle(45, 0, 3.5f, 16, 0.92f, 0.72f, 0.40f);
    glPopMatrix();
}

void drawEarthSpace() {
    glPushMatrix();
    glTranslatef(-70, 0, 0);
    glRotatef(earthOrbit, 0, 0, 1);
    drawCircle(65, 0, 7, 22, 0.08f, 0.25f, 0.65f);
    drawCircle(65, 0, 5, 18, 0.12f, 0.40f, 0.75f);
    drawCircle(63, 2, 2.5f, 10, 0.15f, 0.60f, 0.18f);
    drawCircle(66, -1, 3.0f, 10, 0.18f, 0.55f, 0.15f);
    glColor3f(0.45f, 0.65f, 1.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 28; i++) {
        float a = i * 2.0f * PI / 28;
        glVertex2f(65 + 7.5f * cosf(a), 7.5f * sinf(a));
    }
    glEnd();
    glPushMatrix();
    glTranslatef(65, 0, 0);
    glRotatef(earthOrbit * 2, 0, 0, 1);
    drawCircle(12, 0, 1.8f, 14, 0.72f, 0.72f, 0.75f);
    drawCircle(12, 0, 1.0f, 10, 0.88f, 0.88f, 0.90f);
    glPopMatrix();
    glPopMatrix();
}

void drawMarsSpace() {
    glPushMatrix();
    glTranslatef(-70, 0, 0);
    glRotatef(earthOrbit * 0.5f, 0, 0, 1);
    drawCircle(88, 0, 5.5f, 22, 0.72f, 0.42f, 0.12f);
    drawCircle(88, 0, 4.0f, 18, 0.82f, 0.55f, 0.20f);
    drawCircle(88 + 9 * cosf(floatY * 0.15f), 9 * sinf(floatY * 0.15f), 1.0f, 10, 0.65f, 0.62f, 0.58f);
    drawCircle(88 + 14 * cosf(floatY * 0.08f), 14 * sinf(floatY * 0.08f), 0.8f, 8, 0.72f, 0.68f, 0.65f);
    glPopMatrix();
}

void drawSpaceRocket() {
    glPushMatrix();
    glTranslatef(30, shipY, 0);
    glScalef(2.5f, 2.5f, 1.0f);
    float spFlame = (sinf(floatY * 2.0f) + 1.0f) * 0.5f;
    glColor3f(1.0f, 0.40f + spFlame * 0.25f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-6, 0);
    glVertex2f(6, 0);
    glVertex2f(0, -18.0f - spFlame * 10.0f);
    glEnd();
    glColor3f(1.0f, 0.85f, 0.25f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-3, 0);
    glVertex2f(3, 0);
    glVertex2f(0, -10.0f - spFlame * 6.0f);
    glEnd();
    drawRect(-8, 0, 16, 45, 0.92f, 0.92f, 0.95f);
    drawRect(-4, 0, 8, 45, 0.97f, 0.97f, 1.0f);
    glColor3f(0.10f, 0.30f, 0.75f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-8, 45);
    glVertex2f(8, 45);
    glVertex2f(0, 60);
    glEnd();
    glColor3f(0.15f, 0.40f, 0.85f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-4, 45);
    glVertex2f(4, 45);
    glVertex2f(0, 58);
    glEnd();
    glColor3f(0.08f, 0.25f, 0.65f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-8, 5);
    glVertex2f(-16, -5);
    glVertex2f(-8, 15);
    glVertex2f(8, 5);
    glVertex2f(16, -5);
    glVertex2f(8, 15);
    glEnd();
    glColor3f(0.38f, 0.38f, 0.42f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-8, 8);
    glVertex2f(-12, -2);
    glVertex2f(8, 8);
    glVertex2f(12, -2);
    glEnd();
    drawCircle(0, 32, 4.5f, 18, 0.38f, 0.38f, 0.42f);
    drawCircle(0, 32, 3.5f, 16, 0.08f, 0.18f, 0.50f);
    drawCircle(-1, 33, 1.0f, 10, 0.55f, 0.75f, 1.0f);
    drawCircle(0, 18, 4.5f, 18, 0.38f, 0.38f, 0.42f);
    drawCircle(0, 18, 3.5f, 16, 0.08f, 0.18f, 0.50f);
    drawCircle(-1, 19, 1.0f, 10, 0.55f, 0.75f, 1.0f);
    drawRect(-8, 25, 16, 2, 0.08f, 0.25f, 0.65f);
    drawRect(-8, 11, 16, 2, 0.08f, 0.25f, 0.65f);
    glPopMatrix();
}

void drawSpaceAstronaut() {
    float astroY = clampFloat(astroFollowY, -40.0f, 40.0f);
    drawAstronaut(-30, astroY + floatY, sinf(floatY * 2) * 0.5f, sinf(floatY * 1.5f) * 0.3f, tiltAngle, 0.6f);
}

void drawSpaceUI() {
    if (planetsPaused) {
        glColor3f(1.0f, 0.5f, 0.2f);
        drawLabel(-95, 92, "PLANETS PAUSED (P to resume)", GLUT_BITMAP_HELVETICA_12);
    } else {
        glColor3f(0.5f, 0.5f, 0.5f);
        drawLabel(-95, 92, "P = pause planets", GLUT_BITMAP_HELVETICA_12);
    }

    glColor3f(0.4f, 0.4f, 0.4f);
    drawLabel(-95, -95, "Click rocket = boost | P = pause | Move mouse = astronaut follows", GLUT_BITMAP_HELVETICA_10);
}

// ==================== SPACE SCENE ====================

void drawSpaceScene() {
    drawSpaceBackground();
    drawSpaceStars();
    drawMeteors();
    drawSun();
    drawMercury();
    drawVenus();
    drawEarthSpace();
    drawMarsSpace();
    drawSpaceRocket();
    drawSpaceAstronaut();
    drawSpaceUI();
}

// ============================================================
//  DEV3 SCENES - Stubs
// ============================================================
void drawJourneyScene() {
    drawRect(-100, -100, 200, 200, 0.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    drawLabel(-30, 0, "Coming in Phase 3", GLUT_BITMAP_HELVETICA_18);
}
void drawJupiterLandingScene() {
    drawRect(-100, -100, 200, 200, 0.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    drawLabel(-30, 0, "Coming in Phase 3", GLUT_BITMAP_HELVETICA_18);
}

// ============================================================
//  DEV4 SCENES - Stubs
// ============================================================
void drawWakeUpScene() {
    drawRect(-100, -100, 200, 200, 0.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    drawLabel(-30, 0, "Coming in Phase 4", GLUT_BITMAP_HELVETICA_18);
}
void drawThankYouScene() {
    drawRect(-100, -100, 200, 200, 0.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    drawLabel(-30, 0, "Coming in Phase 4", GLUT_BITMAP_HELVETICA_18);
}

// ============================================================
//  DEV2 - SCENE 6: WALL ZOOM - OBJECT FUNCTIONS
// ============================================================

void drawWallBackground() {
    glBegin(GL_QUADS);
    glColor3f(0.20f, 0.55f, 0.60f);
    glVertex2f(-100, 100);
    glVertex2f(100, 100);
    glColor3f(0.18f, 0.48f, 0.55f);
    glVertex2f(100, 40);
    glVertex2f(-100, 40);
    glColor3f(0.10f, 0.25f, 0.30f);
    glVertex2f(100, -20);
    glVertex2f(-100, -20);
    glEnd();
    drawRect(-100, -100, 200, 80, 0.55f, 0.18f, 0.12f);
}

void drawWallFan() {
    drawRect(-1, 80, 2, 20, 0.18f, 0.18f, 0.20f);
    glPushMatrix();
    glTranslatef(0, 80, 0);
    glRotatef(fanSpin, 0, 0, 1);
    drawCircle(0, 0, 3.5f, 18, 0.28f, 0.28f, 0.30f);
    drawRect(-22, -2, 18, 3.5f, 0.35f, 0.18f, 0.10f);
    drawRect(4, -2, 18, 3.5f, 0.35f, 0.18f, 0.10f);
    glPopMatrix();
}

void drawWallWindow() {
    drawRect(-35, 11, 70, 64, 0.22f, 0.12f, 0.06f);
    drawRect(-31, 15, 62, 56, 0.0f, 0.0f, 0.02f);
}

void drawWallWindowStars() {
    drawCircle(-20, 60, 0.6f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(-10, 48, 0.6f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(-2, 62, 0.6f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(8, 52, 0.6f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(18, 63, 0.6f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(22, 42, 0.6f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(12, 31, 0.6f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(-18, 34, 0.6f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(-5, 25, 0.6f, 8, 1.0f, 1.0f, 1.0f);
    drawCircle(24, 23, 0.6f, 8, 1.0f, 1.0f, 1.0f);
    glColor3f(0.22f, 0.12f, 0.06f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(0, 15);
    glVertex2f(0, 71);
    glVertex2f(-31, 43);
    glVertex2f(31, 43);
    glEnd();
}

void drawWallBookshelf() {
    drawRect(44, -20, 36, 55, 0.38f, 0.20f, 0.06f);
    drawRect(47, 20, 30, 2, 0.32f, 0.16f, 0.05f);
    drawRect(47, 0, 30, 2, 0.32f, 0.16f, 0.05f);
    drawRect(49, 22, 5, 12, 0.60f, 0.15f, 0.10f);
    drawRect(55, 22, 4, 10, 0.10f, 0.45f, 0.60f);
    drawRect(60, 22, 6, 11, 0.70f, 0.55f, 0.10f);
}

void drawWallTreePot() {
    glColor3f(0.50f, 0.25f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(50, 53);
    glVertex2f(70, 53);
    glVertex2f(66, 37);
    glVertex2f(54, 37);
    glEnd();
    drawRect(59, 53, 2, 14, 0.10f, 0.30f, 0.10f);
    drawCircle(60, 67, 9, 18, 0.10f, 0.50f, 0.12f);
    drawCircle(52, 62, 6, 16, 0.08f, 0.42f, 0.10f);
    drawCircle(68, 62, 6, 16, 0.08f, 0.42f, 0.10f);
}

void drawWallBoxes() {
    drawRect(-76, -20, 14, 8, 0.12f, 0.45f, 0.55f);
    drawRect(-76, -12, 14, 2, 0.88f, 0.72f, 0.28f);
    drawRect(-76, -10, 14, 8, 0.60f, 0.15f, 0.10f);
    drawRect(-59, -20, 14, 8, 0.10f, 0.55f, 0.25f);
}

// ==================== WALL SCENE ====================

void drawWallScene() {
    glPushMatrix();
    float zoom = 1.0f;
    if (wallTimer > 1.5f) {
        float zt = wallTimer - 1.5f;
        float zProg = smoothStep(zt / 6.0f);
        zoom = 1.0f + zProg * 5.0f;
    }
    glTranslatef(0.0f, 43.0f, 0.0f);
    glScalef(zoom, zoom, 1.0f);
    glTranslatef(0.0f, -43.0f, 0.0f);

    drawWallBackground();
    drawWallFan();
    drawWallWindow();
    drawWallWindowStars();
    drawWallBookshelf();
    drawWallTreePot();
    drawWallBoxes();

    glPopMatrix();
}

// ============================================================
//  FLOATING TREEHOUSE - OBJECT FUNCTIONS
// ============================================================

void drawTreehouseBackground() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.02f);
    glVertex2f(-100, -100);
    glVertex2f(100, -100);
    glColor3f(0.02f, 0.04f, 0.10f);
    glVertex2f(100, 100);
    glVertex2f(-100, 100);
    glEnd();
}

void drawJupiterTreehouse() {
    float jupRot = treehouseTimer * 2.0f;
    drawCircle(38, 32, 52, 55, 0.92f, 0.52f, 0.18f);
    drawCircle(38, 32, 40, 50, 1.0f, 0.65f, 0.30f);
    drawCircle(38, 32, 24, 45, 1.0f, 0.80f, 0.48f);
    glColor3f(0.85f, 0.45f, 0.12f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(10, 25 + sinf(jupRot * 0.1f) * 2);
    glVertex2f(66, 25 + sinf(jupRot * 0.1f + 1) * 2);
    glVertex2f(8, 35 + sinf(jupRot * 0.15f) * 1.5f);
    glVertex2f(68, 35 + sinf(jupRot * 0.15f + 2) * 1.5f);
    glEnd();
}

void drawEarthTreehouse() {
    float earthRot = treehouseTimer * 5.0f;
    drawCircle(-92, -20, 115, 115, 0.02f, 0.10f, 0.20f);
    drawCircle(-88, -16, 105, 115, 0.04f, 0.28f, 0.45f);
    drawCircle(-112, 28, 22, 38, 0.18f, 0.52f, 0.30f);
    drawCircle(-78, 48, 28, 38, 0.20f, 0.58f, 0.34f);
    drawCircle(-48, -4, 24, 38, 0.16f, 0.48f, 0.28f);
    float iceX = cosf(earthRot * 0.02f) * 5.0f;
    drawCircle(-92 + iceX, 60, 18, 25, 0.90f, 0.90f, 0.86f);
    drawCircle(-88 - iceX, -60, 22, 28, 0.84f, 0.86f, 0.84f);
}

void drawTreehouseStars() {
    for (int i = 0; i < 20; i++) {
        float sx = (i * 37 + 15) % 200 - 100;
        float sy = (i * 53 + 20) % 180 - 80;
        float twk = (sinf(treehouseTimer * 3.0f + i * 1.1f) + 1.0f) * 0.5f;
        drawCircle(sx, sy, 0.3f + twk * 0.4f, 8, 1.0f, 1.0f, 1.0f);
    }
}

void drawTreehouseShootingStar() {
    float shotX = fmodf(treehouseTimer * 30.0f, 250.0f) - 125.0f;
    float shotY = 70.0f - shotX * 0.3f + sinf(treehouseTimer) * 5.0f;
    if (treehouseTimer > 3.0f && treehouseTimer < 5.0f) {
        glColor3f(0.9f, 0.95f, 1.0f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
        glVertex2f(shotX, shotY);
        glVertex2f(shotX - 15.0f, shotY + 5.0f);
        glEnd();
        drawCircle(shotX, shotY, 0.5f, 6, 1.0f, 1.0f, 1.0f);
    }
}

void drawFloatingIsland() {
    glColor3f(0.20f, 0.14f, 0.08f);
    glBegin(GL_POLYGON);
    glVertex2f(28, -8);
    glVertex2f(78, -8);
    glVertex2f(88, -18);
    glVertex2f(70, -38);
    glVertex2f(56, -62);
    glVertex2f(42, -38);
    glVertex2f(20, -18);
    glEnd();
}

void drawTreeTrunk() {
    glColor3f(0.22f, 0.15f, 0.09f);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
    glVertex2f(56, -62);
    glVertex2f(56, -78);
    glVertex2f(50, -58);
    glVertex2f(48, -72);
    glVertex2f(62, -58);
    glVertex2f(64, -70);
    glEnd();
}

void drawTreeCanopy() {
    drawRect(26, -9, 54, 8, 0.18f, 0.45f, 0.14f);
}

void drawTreeRoots() {
    glColor3f(0.28f, 0.18f, 0.10f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(42, -20);
    glVertex2f(35, -42);
    glVertex2f(55, -24);
    glVertex2f(50, -58);
    glVertex2f(66, -22);
    glVertex2f(72, -48);
    glEnd();
}

void drawTreehouseHouse() {
    drawRect(53, -10, 5, 30, 0.35f, 0.20f, 0.08f);
    drawCircle(55, 28, 16, 25, 0.08f, 0.38f, 0.10f);
    drawCircle(46, 24, 12, 22, 0.06f, 0.32f, 0.08f);
    drawCircle(64, 24, 12, 22, 0.06f, 0.32f, 0.08f);
    drawRect(40, 0, 30, 22, 0.45f, 0.30f, 0.15f);
    drawRect(43, 3, 24, 16, 0.58f, 0.40f, 0.24f);
}

void drawTreehouseDoor() {
    drawRect(51, 3, 8, 12, 0.20f, 0.12f, 0.06f);
    float lf = (sinf(treehouseTimer * 8.0f) + 1.0f) * 0.15f + 0.70f;
    drawCircle(55, 9, 0.8f, 8, 0.88f * lf, 0.70f * lf, 0.22f * lf);
    drawRect(43, 10, 7, 7, 0.88f, 0.72f, 0.30f);
    drawRect(60, 10, 7, 7, 0.88f, 0.72f, 0.30f);
    float doorOpen = 0.0f;
    if (treehouseTimer > 1.0f && treehouseTimer < 6.0f) {
        doorOpen = sinf((treehouseTimer - 1.0f) * 0.8f) * 5.0f;
    }
    glPushMatrix();
    glTranslatef(51, 0, 0);
    glRotatef(doorOpen, 0, 1, 0);
    drawRect(-3, 0, 6, 14, 0.30f, 0.18f, 0.08f);
    drawCircle(2, 7, 0.5f, 8, 0.80f, 0.65f, 0.20f);
    glPopMatrix();
}

void drawTreehouseRoof() {
    glColor3f(0.12f, 0.16f, 0.22f);
    glBegin(GL_TRIANGLES);
    glVertex2f(36, 22);
    glVertex2f(74, 22);
    glVertex2f(55, 38);
    glEnd();
    glColor3f(0.18f, 0.24f, 0.32f);
    glBegin(GL_TRIANGLES);
    glVertex2f(40, 22);
    glVertex2f(70, 22);
    glVertex2f(55, 34);
    glEnd();
    drawCircle(55, 36, 8, 18, 0.10f, 0.42f, 0.14f);
    drawCircle(48, 30, 6, 16, 0.08f, 0.36f, 0.10f);
    drawCircle(62, 30, 6, 16, 0.08f, 0.36f, 0.10f);
}

void drawBoyWalkingTreehouse() {
    float bob = sinf(treehouseTimer * 1.2f) * 3.0f;
    if (treehouseTimer > 2.0f && treehouseTimer < 6.5f) {
        float wp = (treehouseTimer - 2.0f) / 4.5f;
        if (wp > 1.0f) {
            wp = 1.0f;
        }
        float bx = 55.0f + wp * 20.0f;
        float by = -8.0f + bob + sinf(wp * PI) * 8.0f;
        drawRect(bx - 3, by - 10, 6, 12, 0.15f, 0.35f, 0.70f);
        float ls = sinf(treehouseTimer * 6.0f) * 8.0f;
        glPushMatrix();
        glTranslatef(bx, by - 10, 0);
        glRotatef(ls, 0, 0, 1);
        drawRect(-2, 0, 3, 10, 0.85f, 0.70f, 0.55f);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(bx, by - 10, 0);
        glRotatef(-ls, 0, 0, 1);
        drawRect(-1, 0, 3, 10, 0.85f, 0.70f, 0.55f);
        glPopMatrix();
        drawCircle(bx, by + 4, 5, 18, 0.25f, 0.15f, 0.08f);
        drawCircle(bx, by + 3, 4, 18, 0.90f, 0.75f, 0.55f);
        drawCircle(bx - 1.5f, by + 3.5f, 0.8f, 8, 0.0f, 0.0f, 0.0f);
        drawCircle(bx + 1.5f, by + 3.5f, 0.8f, 8, 0.0f, 0.0f, 0.0f);
    }
}

void drawSpeechBubble() {
    if (treehouseTimer >= 2.0f && treehouseTimer < 7.0f) {
        float ba = 1.0f;
        if (treehouseTimer > 5.5f) {
            ba = 1.0f - (treehouseTimer - 5.5f) * 2.0f;
        }
        if (ba < 0.0f) {
            ba = 0.0f;
        }
        drawRect(62, -70, 35, 16, 1.0f, 1.0f, 0.9f);
        glBegin(GL_TRIANGLES);
        glVertex2f(65, -54);
        glVertex2f(60, -58);
        glVertex2f(62, -62);
        glEnd();
        glColor4f(0.0f, 0.0f, 0.0f, ba);
        if (treehouseTimer < 3.5f) {
            drawLabel(65, -65, "What!!", GLUT_BITMAP_HELVETICA_18);
        } else if (treehouseTimer < 5.0f) {
            drawLabel(65, -65, "My treehouse", GLUT_BITMAP_HELVETICA_12);
        } else {
            drawLabel(65, -65, "is in space!", GLUT_BITMAP_HELVETICA_12);
        }
    }
}

// ==================== TREEHOUSE SCENE ====================

void drawTreehouseScene() {
    drawTreehouseBackground();
    drawJupiterTreehouse();
    drawEarthTreehouse();
    drawTreehouseStars();
    drawTreehouseShootingStar();

    float bob = sinf(treehouseTimer * 1.2f) * 3.0f;
    float tilt = sinf(treehouseTimer * 0.8f) * 1.5f;
    glPushMatrix();
    glTranslatef(0, bob, 0);
    glRotatef(tilt, 0, 0, 1);

    drawFloatingIsland();
    drawTreeTrunk();
    drawTreeCanopy();
    drawTreeRoots();
    drawTreehouseHouse();
    drawTreehouseDoor();
    drawTreehouseRoof();
    glPopMatrix();

    drawBoyWalkingTreehouse();
    drawSpeechBubble();
}

// ============================================================
//  CALLBACKS
// ============================================================

void resetAllState() {
    fanSpin = 0.0f;
    clockTime = 0.0f;
    mousePosX = -130.0f;
    lampLit = false;
    lampGlow = 0.0f;
    boyAsleep = false;
    dreamActive = false;
    sleepCount = 0.0f;
    zoomLevel = 1.0f;
    spaceMode = false;
    treehouseMode = false;
    wallMode = false;
    wakeMode = false;
    journeyActive = false;
    jupiterLanding = false;
    starsReady = false;
    starsInitDone = false;
    shipY = -130.0f;
    rocketBoost = 0.0f;
    planetsPaused = false;
    mercuryOrbit = 0.0f;
    venusOrbit = 0.0f;
    earthOrbit = 0.0f;
    wallTimer = 0.0f;
    treehouseTimer = 0.0f;
    fanSpeed = 15.0f;
    floatY = 0.0f;
    tiltAngle = 0.0f;
    journeyTimer = 0.0f;
    jupiterSize = 5.0f;
    rocketJourneyX = 0.0f;
    marsPhase = 0;
    marsTimer = 0.0f;
    marsPhaseTimer = 0.0f;
    landRocketY = 90.0f;
    girlWalkX = 8.0f;
    alienAppear = 0.0f;
    escapeRocketY = -45.0f;
    warningAlpha = 0.0f;
    wakeTimer = 0.0f;
    wakeHeadLift = 0.0f;
    wakeHeadTurn = 0.0f;
    wakeSpeed = 1.0f;
    for (int i = 0; i < 5; i++) {
        alienDodgeX[i] = 0;
        alienDodgeY[i] = 0;
    }
    laserActive = 0.0f;
    astroAimAngle = 0.0f;
    dreamCloudX = 0.0f;
    dreamCloudY = 0.0f;
    dreamPopped = false;
    thankyouMode = false;
    thankyouTimer = 0.0f;
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float wx = ((float)x / 1000.0f) * 200.0f - 100.0f;
        float wy = 100.0f - ((float)y / 800.0f) * 200.0f;

        if (spaceMode && !wallMode && !treehouseMode && !journeyActive && !jupiterLanding && !wakeMode) {
            if (rocketBoost == 0.0f) {
                rocketBoost = 3.0f;
            }
        }

        if (!spaceMode && !wallMode && !treehouseMode && !journeyActive && !jupiterLanding && !wakeMode) {
            float dx = wx - (-30.0f);
            float dy = wy - (0.0f);
            if (dx * dx + dy * dy <= 400.0f) {
                lampLit = !lampLit;
            }

            if (dreamActive && !dreamPopped && sleepCount > 9.5f) {
                float dcx = wx - dreamCloudX;
                float dcy = wy - (dreamCloudY + 65.0f);
                if (dcx * dcx + dcy * dcy <= 400.0f) {
                    dreamPopped = true;
                }
            }
        }
    }
}

void mouseMove(int x, int y) {
    gMouseWX = ((float)x / 1000.0f) * 200.0f - 100.0f;
    gMouseWY = 100.0f - ((float)y / 800.0f) * 200.0f;
    if (spaceMode) {
        astroFollowY = gMouseWY * 0.3f;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key >= '1' && key <= '8') {
        resetAllState();
        if (key == '2') {
            spaceMode = true;
            sleepCount = 11.0f;
            zoomLevel = 21.0f;
            shipY = -130.0f;
        }
        if (key == '3') {
            journeyActive = true;
            journeyTimer = 0.0f;
            jupiterSize = 5.0f;
        }
        if (key == '4') {
            jupiterLanding = true;
            marsPhase = 0;
        }
        if (key == '5') {
            wakeMode = true;
        }
        if (key == '6') {
            wallMode = true;
            wallTimer = 0.0f;
            fanSpin = 0.0f;
        }
        if (key == '7') {
            treehouseMode = true;
            treehouseTimer = 0.0f;
        }
        if (key == '8') {
            thankyouMode = true;
            thankyouTimer = 0.0f;
        }
        glutPostRedisplay();
        return;
    }
    if (key == 'f' || key == 'F') {
        if (fanSpeed > 14.0f) {
            fanSpeed = 40.0f;
        } else if (fanSpeed > 39.0f) {
            fanSpeed = 0.0f;
        } else {
            fanSpeed = 15.0f;
        }
        glutPostRedisplay();
    }
    if (key == 'p' || key == 'P') {
        planetsPaused = !planetsPaused;
        glutPostRedisplay();
    }
    if (key == 'e' || key == 'E') {
        if (wakeMode) {
            wakeHeadLift = 3.0f;
            wakeHeadTurn = 18.0f;
            wakeTimer = 6.0f;
        }
    }
    if (key == 'r' || key == 'R') {
        resetAllState();
        glutPostRedisplay();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (treehouseMode) {
        drawTreehouseScene();
    } else if (thankyouMode) {
        drawThankYouScene();
    } else if (wallMode) {
        drawWallScene();
    } else if (wakeMode) {
        drawWakeUpScene();
    } else if (journeyActive) {
        drawJourneyScene();
    } else if (jupiterLanding) {
        drawJupiterLandingScene();
    } else if (spaceMode) {
        drawSpaceScene();
    } else {
        if (zoomLevel > 1.0f) {
            glTranslatef(12, 65, 0);
            glScalef(zoomLevel, zoomLevel, 1.0f);
            glTranslatef(-12, -65, 0);
        }
        drawBedroomScene();
    }
    glutSwapBuffers();
}

void timerFunc(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timerFunc, 0);

    float lampTarget = lampLit ? 1.0f : 0.0f;
    lampGlow += (lampTarget - lampGlow) * 0.08f;

    if (wakeMode) {
        wakeTimer += DT;
        if (wakeTimer >= 6.0f) {
            wakeMode = false;
            wallMode = true;
            wallTimer = 0.0f;
            fanSpin = 0.0f;
        }
        return;
    }
    if (wallMode) {
        wallTimer += DT;
        fanSpin += fanSpeed;
        if (fanSpin > 360) {
            fanSpin -= 360;
        }
        if (wallTimer >= 7.5f) {
            wallMode = false;
            treehouseMode = true;
            treehouseTimer = 0.0f;
        }
        return;
    }
    if (treehouseMode) {
        treehouseTimer += DT;
        if (treehouseTimer >= 7.0f) {
            treehouseMode = false;
            thankyouMode = true;
            thankyouTimer = 0.0f;
        }
        return;
    }
    if (thankyouMode) {
        thankyouTimer += DT;
        return;
    }
    if (journeyActive) {
        journeyTimer += DT;
        if (journeyTimer >= 5.0f) {
            journeyActive = false;
            jupiterLanding = true;
            marsPhase = 0;
        }
        return;
    }
    if (jupiterLanding) {
        marsTimer += DT;
        if (marsTimer >= 5.0f) {
            jupiterLanding = false;
            wakeMode = true;
            wakeTimer = 0.0f;
        }
        return;
    }

    fanSpin += fanSpeed;
    clockTime += 0.05f;
    mousePosX += 1.5f;
    sleepCount += DT;
    if (fanSpin > 360) {
        fanSpin -= 360;
    }
    if (clockTime > 360) {
        clockTime -= 360;
    }
    if (mousePosX > 130) {
        mousePosX = -130;
    }
    if (sleepCount >= 7.0f) {
        boyAsleep = true;
    }
    if (sleepCount >= 8.0f) {
        dreamActive = true;
    }
    if (sleepCount >= 11.0f && !spaceMode) {
        zoomLevel += 0.2f;
        if (zoomLevel > 20.0f) {
            spaceMode = true;
        }
    }
    if (spaceMode) {
        if (!planetsPaused) {
            floatY += DT;
            tiltAngle = sinf(floatY * 0.5f) * 5.0f;
            mercuryOrbit += 2.0f;
            venusOrbit += 1.2f;
            earthOrbit += 0.7f;
        }
        shipY += 0.9f;
        if (rocketBoost > 0.0f) {
            shipY += rocketBoost;
            rocketBoost -= 0.1f;
            if (rocketBoost < 0.0f) {
                rocketBoost = 0.0f;
            }
        }
        if (shipY > 150.0f && !journeyActive) {
            journeyActive = true;
            journeyTimer = 0.0f;
            jupiterSize = 5.0f;
        }
    }
}

void init() {
    srand(time(NULL));
    glClearColor(0.48f, 0.75f, 0.92f, 1.0f);
    glDisable(GL_DITHER);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(100, 80);
    glutCreateWindow("Celestial Dreams");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
    glutPassiveMotionFunc(mouseMove);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timerFunc, 0);

    glutMainLoop();

    return 0;
}
