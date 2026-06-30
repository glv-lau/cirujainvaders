#include Button.h

Button::Button(const font &font, const string &texto, const Vector2f &position, const Vector2f &size)
{
    // Implementación del constructor
}

Button::~Button()
{
    // Implementación del destructor
}

bool Button::contiene(const Vector2f &mousePos)
{
    return cuadro.getGlobalBounds().contains(mousePos);
}

void Button::seleccionar(bool selected)
{
    if (selected)
    {
        cuadro.setFillColor(Color::Green); // Color cuando el botón está seleccionado
    }
    else
    {
        cuadro.setFillColor(Color::White); // Color por defecto
    }
}
if (event.type == Event::MouseButtonPressed)
{
    if (event.mouseButton.button == Mouse::Left)
    {
        Vector2f mouse =
            window.mapPixelToCoords(
                mouse::getPosition(window));
        if (playButton.contiene(mouse))
        {
            // Acción cuando se presiona el botón
        }
        if (exitButton.contiene(mouse))
        {
            window.close(); // Cierra la ventana si se presiona el botón de salir
        }
    }
}