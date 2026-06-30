Class Button {
    public:
        Button(const font& font, const string& texto, const Vector2f& position, const Vector2f& size);
        virtual ~Button();
        virtual void draw(RenderWindow &window) = 0;
        virtual void update() = 0;
        bool contiene(const Vector2f& mousePos);
        void seleccionar(bool selected);
    private:
        bool m_isPressed;
        RectangleShape cuadro;
        text m_texto;

};