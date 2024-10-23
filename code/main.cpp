#include <core/window_manager.hpp>

#include <opengl/functions_loader.hpp>
#include <opengl/vertex_array.hpp>
#include <opengl/commands.hpp>
#include <opengl/pipeline.hpp>

#include <math/vec3.hpp>

using namespace engine;

const int win_width = 800;
const int win_height = 600;

float triangle_x = win_width / 2.0f;
float triangle_y = win_height / 2.0f;
float triangle_size = 100.0f;

float step_x = 0.2f;
float step_y = 0.1f;

void DrawTriangle(float x, float y, float size)
{
    float scale_x = (float)win_width / size;
    float scale_y = (float)win_height / size;

    std::vector<math::vec3> vertices
    {
        { -1.0f, -1.0f, 0.0f },
        {  1.0f, -1.0f, 0.0f },
        {  0.0f,  1.0f, 0.0f }
    };

    math::vec3 pos_transform{ x / (win_width / 2.0f) - 1.0f, -(y / (win_height / 2.0f) - 1.0f), 0.0f };
    math::vec3 scale{ 1.0f / scale_x, 1.0f / scale_y, 1.0f };

    for (auto&& v : vertices)
    {
        v.h_product(scale);
        v.add(pos_transform);
    }

    gl::Buffer vertex_buffer;
    vertex_buffer.create();
    vertex_buffer.data(core::BufferData::create(vertices));

    gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.attach_vertices(vertex_buffer, sizeof(math::vec3));
    vertex_array.attribute({ 0, 3, gl::type_float });

    vertex_array.bind();
    gl::Commands::draw_arrays(gl::triangles, vertices.size());

    vertex_buffer.destroy();
    vertex_array.destroy();

}

void Draw()
{
    DrawTriangle(triangle_x, triangle_y, triangle_size);
}

void Update()
{
    triangle_x += step_x;
    triangle_y += step_y;

    if (triangle_x >= win_width || triangle_x <= 0)
    {
        step_x = -step_x;
    }

    if (triangle_y >= win_height || triangle_y <= 0)
    {
        step_y = -step_y;
    }
}

int32_t main()
{
    core::Context::init_extensions();

    core::WindowManager::instance().create({ });
    core::WindowManager::instance().display();

    gl::FunctionsLoader::init_core();
    gl::FunctionsLoader::init_extensions();


    gl::Pipeline::enable(gl::framebuffer_srgb);




    while (core::WindowManager::instance().is_active())
    {
        gl::Commands::clear(1.0f, 0.5f, 0.0f);
        gl::Commands::clear(gl::color_buffer_bit);

        Draw();
        Update();

        core::WindowManager::instance().update();
    }

    core::WindowManager::instance().destroy();

    return 0;
}