# GameEngine

> A C++ and OpenGL game engine similar to unity

![](https://i.imgur.com/9InEv7c.png)

## Current Features
- Basic C# Scripting using mono
- Renderer with support for sprites and uniform colours
- Entity-Component system using entt

## Future Plans
- Expand scripting features
- Include save file/project system
- Add physics
- Add Input System

## Scripting Example:

```cs
namespace ScriptingExample
{
    public class ExampleScript : EntityScript
    {
        Transform t;

        float v_x = 0;
        float v_y = -1;

        public override void OnStart()
        {
            t = GetTransform();
        }

        public override void OnUpdate()
        {
            t.Translate(deltaTime * v_x, deltaTime * v_y, 0);
        }
    }
}
```
