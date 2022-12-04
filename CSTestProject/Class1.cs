using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CSTestProject.Engine;

namespace CSTestProject
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

    public class TestScript : EntityScript
    {
        Transform t;

        float timer = 0;

        public override void OnStart()
        {
            t = GetTransform();
        }

        public override void OnUpdate()
        {
            t.Translate(0, deltaTime * (float) Math.Cos(timer), 0);

            timer += deltaTime;
        }
    }
}
