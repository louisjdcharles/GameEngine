using System.Runtime.CompilerServices;


namespace CSTestProject.Engine
{
    public class Transform
    {
        private uint owner_id;
        private ulong registry_ptr = 0;

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void __TranslateInternal(ulong registry_ptr, uint id, float x, float y, float z);

        /*[MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static Vector3 __GetPositionInternal(ulong registry_ptr, uint id);*/

        public void Translate(float x, float y, float z) {
            __TranslateInternal(registry_ptr, owner_id, x, y, z);
        }

        public void Translate(Vector3 v) {
            __TranslateInternal(registry_ptr, owner_id, v.x, v.y, v.z);
        }

        /*public Vector3 GetPosition() { 
            return __GetPositionInternal(registry_ptr, owner_id);
        }*/

        public Transform(uint id, ulong reg) { owner_id = id; registry_ptr = reg; }
    }

    public struct Vector3
    {
        public float x, y, z;

        public Vector3(float x, float y, float z) { this.x = x; this.y = y; this.z = z; }
    }

    public class EntityScript
    {
        private uint __internal_id = 0;
        private ulong __registry_ptr = 0;

        protected static float deltaTime = 0;

        public Transform GetTransform() {
            return new Transform(__internal_id, __registry_ptr);
        }
        public virtual void OnStart() { }
        public virtual void OnUpdate() { }

        protected EntityScript() {  }

    }
}
