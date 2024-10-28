#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define HEADER_SIZE 64

#define FONT_SIZE 24
#define PADDING_X 48
#define PADDING_Y 24
#define BUTTONS_GAP 24

typedef enum ButtonState {
    DEFAULT,
    HOVER,
} ButtonState;

typedef struct Button {
    Rectangle rect;
    ButtonState state;
    const char *text;
} Button;

const int screenWidth = 800;
const int screenHeight = 600;

bool yes_clicked = false;
Button yes_button;
Button no_button;

Button init_button(int posX, int posY, const char* text)
{
    int text_width = MeasureText(text, FONT_SIZE);
    Rectangle rect = {
        .x = posX,
        .y = posY,
        .width = text_width + PADDING_X,
        .height = FONT_SIZE + PADDING_Y
    };

    Button button = {
        .rect = rect,
        .text = text,
        .state = DEFAULT,
    };

    return button;
}

void render_button(Button button)
{
    int text_width = MeasureText(button.text, FONT_SIZE);
    DrawRectangleRounded(button.rect, 0.2, 24, button.state == HOVER ? GRAY : BLACK);

    DrawText(
        button.text,
        button.rect.x + button.rect.width / 2 - text_width / 2.,
        button.rect.y + button.rect.height / 2 - FONT_SIZE / 2. ,
        FONT_SIZE,
        WHITE
    );
}

void render_initial_text() {
    const char *text = "SOSAL???";
    int text_width = MeasureText(text, FONT_SIZE);
    DrawText(text, screenWidth / 2 - text_width / 2, 200, FONT_SIZE, BLACK);
}

void render_ending_text() {
    const char *text = "TAK I ZNAL!!!";
    int text_width = MeasureText(text, FONT_SIZE);
    DrawText(text, screenWidth / 2 - text_width / 2, 200, FONT_SIZE, BLACK);
}

void init()
{
    srand(time(NULL));

    InitWindow(screenWidth, screenHeight, "TEST NA SOSAL");
    SetTargetFPS(60);

    yes_button = init_button(0, 0, "Da");
    no_button = init_button(0, 0, "Net");

    int a = yes_button.rect.width + no_button.rect.width + BUTTONS_GAP;

    yes_button.rect.x = screenWidth / 2. - a / 2.;
    no_button.rect.x = screenWidth / 2. - a / 2. + yes_button.rect.width + BUTTONS_GAP;

    yes_button.rect.y = 400;
    no_button.rect.y = 400;
}

void on_yes_mouse_over()
{
    yes_button.state = HOVER;
}

void on_yes_click()
{
    yes_clicked = true;
}

void on_yes_mouse_out()
{
    yes_button.state = DEFAULT;
}

void on_no_mouse_over()
{
    no_button.rect.x = rand() % (screenWidth - (int)no_button.rect.width);
    no_button.rect.y = rand() % (screenHeight - (int)no_button.rect.height);
}

bool is_mouse_over_button(Rectangle button_rect)
{
    return CheckCollisionPointRec(GetMousePosition(), button_rect);
}

void update()
{
    if (is_mouse_over_button(yes_button.rect)) {
        on_yes_mouse_over();
    } else {
        on_yes_mouse_out();
    }

    if (is_mouse_over_button(yes_button.rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        on_yes_click();
    }

    if (is_mouse_over_button(no_button.rect)) {
        on_no_mouse_over();
    }
}


void loop()
{
    update();

    BeginDrawing();

    ClearBackground(WHITE);

    if (!yes_clicked) {
        render_initial_text();
        render_button(yes_button);
        render_button(no_button);
    } else {
        render_ending_text();
    }

    EndDrawing();
}

int main()
{
    init();

    while (!WindowShouldClose()) {
        loop();
    }

    CloseWindow();

    return 0;
}
