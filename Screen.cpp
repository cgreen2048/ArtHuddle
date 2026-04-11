#include "Screen.hpp"

Screen::Screen() : width{0}, height{0} {}

Screen::Screen(uint32_t w, uint32_t h, SDL_Renderer* renderer) : Screen() {
    this->width = w;
    this->height = h;
    this->renderer = renderer;
    this->surface = SDL_CreateSurface(w, h, SDL_PIXELFORMAT_RGBA32);
    if (!this->surface) {
        std::cerr << SDL_GetError();
        return;
    }
    this->drawBox(ivec2(0, 0), ivec2(this->width, this->height), ivec3(0, 0, 0), ivec2(0, 0), ivec2(this->width, this->height));
}

Screen::Screen(const Screen& cp) : Screen() {
    this->width = cp.width;
    this->height = cp.height;
    this->renderer = cp.renderer;
    this->surface = SDL_CreateSurface(this->width, this->height, SDL_PIXELFORMAT_RGBA32);
    if (!this->surface) {
        std::cerr << SDL_GetError();
        return;
    }
    
    if (this->surface) {
        cp.blitTo(this->surface);
    }
}

Screen::~Screen() {
    if (this->surface != nullptr) {
        SDL_DestroySurface(this->surface);
    }
}


Screen& Screen::operator=(const Screen& cp) {
    if ((this->surface->format != cp.surface->format) || (this->width != cp.width) || (this->height != cp.height)) {
        std::cerr << "Surfaces not compatible\n";
        return *this;
    }

    this->width = cp.width;
    this->height = cp.height;
    this->surface = SDL_CreateSurface(this->width, this->height, SDL_PIXELFORMAT_RGBA32);
    if (!this->surface) {
        std::cerr << SDL_GetError();
        return *this;
    }
    
    cp.blitTo(this->surface);
    
    return *this;
}

bool Screen::operator==(const Screen rhs) {
    if (this->width != rhs.width || this->height != rhs.height) {
        return false;
    }

    if (!this->surfaceEqual(rhs.surface)) {
        return false;
    }

    return true;
}

bool Screen::surfaceEqual(const SDL_Surface* rhs) {
    if (!this->surface || !rhs) {
        return false;
    }

    int pixelBytes = this->surface->pitch * static_cast<int>(this->height);
    if (std::memcmp(this->surface->pixels, rhs->pixels, pixelBytes)) {
        return false;
    }

    return true;
}

void Screen::blitTo(SDL_Surface* target) const {
    if (target == nullptr) {
        std::cerr << "Target surface is a nullptr.\n";
        return;
    }
    bool success = SDL_BlitSurface(this->surface, nullptr, target, nullptr);
    if (!success) {
        std::cerr << SDL_GetError();
    }
}

void Screen::drawBresenhamLine(ivec2 start, ivec2 end, ivec3 color, ivec2 parentStart, ivec2 parentEnd) {
    int x0 = start.x;
    int y0 = start.y;
    int x1 = end.x;
    int y1 = end.y;

    int dx = std::abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1; // sign(+/-) of x

    int dy = -std::abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1; // sign(+/-) of y

    int error = dx + dy;

    
    while (true) {
        if ((x0 >= 0) && (x0 < this->width) && (y0 >= 0) && (y0 < this->height)) {
            colorOnePixel(ivec2(x0, y0), color, parentStart, parentEnd);
        }

        if (x0 == x1 && y0 == y1) {
            break;
        }

        int e2 = 2 * error;

        if (e2 >= dy){
            error += dy;
            x0 += sx;
        }

        if (e2 <= dx){
            error += dx;
            y0 += sy;
        }
    }     
}


bool Screen::pointInTriangle(ivec2 pointA, ivec2 pointB, ivec2 pointC, ivec2 pointP) {
    ivec2 ap = pointP - pointA;
    ivec2 ab = pointB - pointA;
    ivec2 bp = pointP - pointB;
    ivec2 bc = pointC - pointB;
    ivec2 cp = pointP - pointC;
    ivec2 ca = pointA - pointC;

    int crossApAb = ap.cross(ab);
    int crossBpBc = bp.cross(bc);
    int crossCpCa = cp.cross(ca);

    bool hasPositive = crossApAb > 0 || crossBpBc > 0 || crossCpCa > 0;
    bool hasNegative = crossApAb < 0 || crossBpBc < 0 || crossCpCa < 0;

    return !(hasPositive && hasNegative);
}

void Screen::drawTriangle(ivec2 pointA, ivec2 pointB, ivec2 pointC, ivec3 colors, ivec2 parentStart, ivec2 parentEnd) {
    int screenXEnd = static_cast<int>(this->width - 1);
    int screenYEnd = static_cast<int>(this->height - 1);
    
    int minX = std::clamp(std::min({pointA.x, pointB.x, pointC.x}), 0, screenXEnd);
    int maxX = std::clamp(std::max({pointA.x, pointB.x, pointC.x}), 0, screenXEnd);
    int minY = std::clamp(std::min({pointA.y, pointB.y, pointC.y}), 0, screenYEnd);
    int maxY = std::clamp(std::max({pointA.y, pointB.y, pointC.y}), 0, screenYEnd);

    ivec3 clampedColor = ivec3(
        std::clamp(colors.x, MIN_COLOR_VALUE, MAX_COLOR_VALUE),
        std::clamp(colors.y, MIN_COLOR_VALUE, MAX_COLOR_VALUE),
        std::clamp(colors.z, MIN_COLOR_VALUE, MAX_COLOR_VALUE)
    );

    for (int i = minX; i <= maxX; ++i) {
        for (int j = minY; j <= maxY; ++j) {
            ivec2 point = ivec2{i,j};
            if (this->pointInTriangle(pointA, pointB, pointC, point)) {
                this->colorOnePixel(point, clampedColor, parentStart, parentEnd);
            }
        }
    }
}

void Screen::drawEllipse(ivec2 center, int radiusX, int radiusY, ivec3 color, ivec2 parentStart, ivec2 parentEnd) {
    float dx, dy, d1, d2, x = 0, y = radiusY;

    d1 = (radiusY * radiusY) - (radiusX * radiusX * radiusY) + (0.25 * radiusX * radiusX);
    dx = 2 * radiusY * radiusY * x;
    dy = 2 * radiusX * radiusX * y;

    int xCenter = center.x;
    int yCenter = center.y;

    while (dx < dy) 
    {
        // Colors pixels based on 4-way symmetry
        int intX = static_cast<int>(x);
        int intY = static_cast<int>(y);
        for (int i = xCenter - intX; i <= xCenter + intX; ++i) {
            colorOnePixel(ivec2(i, yCenter + intY), color, parentStart, parentEnd);
            colorOnePixel(ivec2(i, yCenter - intY), color, parentStart, parentEnd);
        }

        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * radiusY * radiusY);
            d1 = d1 + dx + (radiusY * radiusY);
        }
        else 
        {
            x++;
            y--;
            dx = dx + (2 * radiusY * radiusY);
            dy = dy - (2 * radiusX * radiusX);
            d1 = d1 + dx - dy + (radiusY * radiusY);
        }
    }

    d2 = ((radiusY * radiusY) * ((x + 0.5) * (x + 0.5))) + 
         ((radiusX * radiusX) * ((y - 1) * (y - 1))) -
          (radiusX * radiusX * radiusY * radiusY);

    while (y >= 0)
    {

        // Colors pixels based on 4-way symmetry
        int intX = static_cast<int>(x);
        int intY = static_cast<int>(y);
        for (int i = xCenter - intX; i <= xCenter + intX; ++i) {
            colorOnePixel(ivec2(i, yCenter + intY), color, parentStart, parentEnd);
            colorOnePixel(ivec2(i, yCenter - intY), color, parentStart, parentEnd);
        }

        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0) 
        {
            y--;
            dy = dy - (2 * radiusX * radiusX);
            d2 = d2 + (radiusX * radiusX) - dy;
        }
        else 
        {
            y--;
            x++;
            dx = dx + (2 * radiusY * radiusY);
            dy = dy - (2 * radiusX * radiusX);
            d2 = d2 + dx - dy + (radiusX * radiusX);
        }
    }
}

void Screen::renderToRenderer(){
    if (!this->renderer || !this->surface){
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
    if(!texture){
        std::cerr << SDL_GetError();
        return;
    }

    SDL_RenderTexture(this->renderer, texture, nullptr, nullptr);
    SDL_DestroyTexture(texture);
}

void Screen::drawTextClipped(ivec2 min, ivec2 max, const std::string& text, ivec3 color)  {
    int padding = 5;
    int boxWidth = max.x - min.x;
    int usableWidth = boxWidth - 2 * padding;
    int maxChars = usableWidth / 8;

    std::string visibleText = text;
    if (static_cast<int>(visibleText.size()) > maxChars) {
        visibleText = visibleText.substr(visibleText.size() - maxChars);
    }

    drawText(ivec2(min.x + padding, min.y + padding), visibleText, color);
}

void Screen::drawCursor(ivec2 pos, ivec3 color) {
    drawText(pos, "|", color);
}

void Screen::drawArrow(ivec2 min, ivec2 max, ivec2 pointA, ivec2 pointB, ivec2 pointC, ivec3 colors, ivec2 parentStart, ivec2 parentEnd) {
    this->drawBox(min, max, colors, parentStart, parentEnd);
    this->drawTriangle(pointA, pointB, pointC, colors, parentStart, parentEnd);
}

void Screen::clear(ivec3 color) {
    this->drawBox(ivec2(0, 0), ivec2(this->width, this->height), color, ivec2(0, 0), ivec2(this->width, this->height));
}

SDL_Surface* Screen::getSurface() {
    return this->surface;
}

uint32_t Screen::getWidth() {
    return this->width;
}

uint32_t Screen::getHeight() {
    return this->height;
}
