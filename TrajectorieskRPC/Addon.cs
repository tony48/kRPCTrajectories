using UnityEngine;

namespace KRPC.Trajectories
{
    [KSPAddon(KSPAddon.Startup.Flight, false)]
    public sealed class Addon : MonoBehaviour
    {
        public void Start()
        {
            TRWrapper.init();
        }
    }
}
