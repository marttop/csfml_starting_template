#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>

typedef struct button {
    sfRectangleShape *rect;
    sfVector2f pos;
    sfVector2f size;
    sfColor color;
    int is_clicked;
} button_t;

button_t *create_button(sfColor color, sfVector2f pos)
{
    button_t *button = malloc(sizeof(button_t));
    button->rect = sfRectangleShape_create();
    button->pos = pos;
    button->size = (sfVector2f){50, 10};
    button->color = color;
    button->is_clicked = 0;

    sfRectangleShape_setFillColor(button->rect, button->color);
    sfRectangleShape_setPosition(button->rect, button->pos);
    sfRectangleShape_setSize(button->rect, button->size);

    return (button);
}

int is_on_button(button_t *button, sfRenderWindow *w)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(w);
    if ((pos.x > button->pos.x && pos.x < button->pos.x + button->size.x) &&
        (pos.y > button->pos.y && pos.y < button->pos.y + button->size.y)) {
        return (1);
    }
    return (0);
}

void event_controll(sfRenderWindow *w, button_t **tab, sfEvent *event)
{
    for (int i = 0; i < 4; i++) {
        if (is_on_button(tab[i], w)) {
            if (event->type == sfEvtMouseButtonPressed) {
                tab[i]->is_clicked = 1;
            }
        }
        if (event->type == sfEvtMouseButtonReleased) {
            tab[i]->is_clicked = 0;
        }
    }
}

void update(sfRenderWindow *w, button_t **tab)
{
    for (int i = 0; i < 4; i++) {
        if (!tab[i]->is_clicked) {
            if (is_on_button(tab[i], w)) {
                sfRectangleShape_setFillColor(tab[i]->rect, (sfColor){200, 180, 87, 255});
            } else {
                sfRectangleShape_setFillColor(tab[i]->rect, tab[i]->color);
            }
        } else {
            sfRectangleShape_setFillColor(tab[i]->rect, (sfColor){255, 255, 255, 255});
        }
    }
}

int main(void)
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfEvent event;
    sfVector2f pos = (sfVector2f){350, 290};
    int offset = 0;

    button_t **tab = malloc(sizeof(button_t) * 4);

    for (int i = 0; i < 4; i++, offset += 40)
        tab[i] = create_button((sfColor){200, 255, 87, 255}, (sfVector2f){pos.x, pos.y + offset});

    // button_t *button = create_button((sfColor){200, 255, 87, 255});
    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return EXIT_FAILURE;
    /* Limit the window framerate */
    sfRenderWindow_setFramerateLimit(window, 60);
    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        update(window, tab);
        while (sfRenderWindow_pollEvent(window, &event)) {
            event_controll(window, tab, &event);
        }
        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        for (int i = 0; i < 4; i++)
            sfRenderWindow_drawShape(window, (sfShape *)tab[i]->rect, 0);

        /* Update the window */
        sfRenderWindow_display(window);
    }
    return EXIT_SUCCESS;
}