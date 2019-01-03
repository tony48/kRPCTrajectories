using System;
using System.Reflection;
using UnityEngine;


namespace KRPC.Trajectories
{
        public class TRWrapper
        {
            public static bool? wrapped = null;
            private static System.Type trajectoriesAPIType = null;
            private static MethodInfo trGetTimeTillImpact = null;
            private static MethodInfo trGetImpactPosition = null;
            private static MethodInfo trCorrectedDirection = null;
            private static MethodInfo trPlannedDirection = null;
            private static MethodInfo trHasTarget = null;
            private static MethodInfo trSetTarget = null;
            private static PropertyInfo trAlwaysUpdate = null;
            private static PropertyInfo trProgradeEntry = null;
            private static PropertyInfo trRetrogradeEntry = null;

            private static Type GetType(string name)
            {
                Type type = null;
                AssemblyLoader.loadedAssemblies.TypeOperation(t =>
                {
                    if (t.FullName == name)
                        type = t;
                });
                return type;
            }


            public static void init()
            {
                AssemblyLoader.loadedAssemblies.TypeOperation(t =>
                {
                    if (t.FullName == "Trajectories.API")
                    {
                      trajectoriesAPIType = t;
                    }
                });
                if (trajectoriesAPIType == null)
                {
                    Debug.Log("[TR-KRPC] Cannot find Trajectories");
                    wrapped = false;
                    return;
                }

                Debug.Log("[TR-KRPC] Trajectories found");
                // Trajectories v2.2.0 API Has version properties. Checking versions here.
                if (trajectoriesAPIType.GetProperty("GetVersion") == null)
                {
                    if (trajectoriesAPIType.GetMethod("HasTarget") == null) // assume pre v2.0.0 (Old API)
                    {
                        GetVersion = "";
                        IsVerTwo = false;
                        IsVerTwoTwo = false;
                    }
                    else // assume v2.0.0 and v2.1.0 (API is identical in these versions)
                    {
                        GetVersion = "2.0.0";
                        IsVerTwo = true;
                        IsVerTwoTwo = false;
                    }
                }
                else // assume v2.2.0 and above (New API)
                {
                    GetVersion = (string)trajectoriesAPIType.GetProperty("GetVersion").GetValue(null, null);
                    IsVerTwo = true;
                    IsVerTwoTwo = true;
                }

                // Method and property checking.
                // Trajectories 2.0.0 changed the capitalization of this method.  Trying both spellings here to support older Trajectories versions:
                trGetImpactPosition = trajectoriesAPIType.GetMethod("GetImpactPosition") ?? trajectoriesAPIType.GetMethod("getImpactPosition");
                if (trGetImpactPosition == null)
                {
                    wrapped = false;
                    return;
                }
                // Trajectories 2.0.0 changed the capitalization of this method.  Trying both spellings here to support older Trajectories versions:
                trCorrectedDirection = trajectoriesAPIType.GetMethod("CorrectedDirection") ?? trajectoriesAPIType.GetMethod("correctedDirection");
                if (trCorrectedDirection == null)
                {
                    wrapped = false;
                    return;
                }
                // Trajectories 2.0.0 changed the capitalization of this method.  Trying both spellings here to support older Trajectories versions:
                trPlannedDirection = trajectoriesAPIType.GetMethod("PlannedDirection") ?? trajectoriesAPIType.GetMethod("plannedDirection");
                if (trPlannedDirection == null)
                {
                    wrapped = false;
                    return;
                }
                // Trajectories 2.0.0 changed the capitalization of this method.  Trying both spellings here to support older Trajectories versions:
                trSetTarget = trajectoriesAPIType.GetMethod("SetTarget") ?? trajectoriesAPIType.GetMethod("setTarget");
                if (trSetTarget == null)
                {
                    wrapped = false;
                    return;
                }
                // Trajectories 2.0.0 changed the capitalization of this method.  Trying both spellings here to support older Trajectories versions:
                trAlwaysUpdate = trajectoriesAPIType.GetProperty("AlwaysUpdate") ?? trajectoriesAPIType.GetProperty("alwaysUpdate");
                if (trAlwaysUpdate == null)
                {
                    wrapped = false;
                    return;
                }
                trAlwaysUpdate.SetValue(null, true, null);
                if ((bool)trAlwaysUpdate.GetValue(null, null) == false)
                {
                    wrapped = false;
                    return;
                }

                // Trajectories v2.0.0 HasTarget method
                if (IsVerTwo)
                {
                    // HasTarget is avalable in Trajectories v2.0.0 and above
                    trHasTarget = trajectoriesAPIType.GetMethod("HasTarget");
                    if (trHasTarget == null)
                    {
                        wrapped = false;
                        return;
                    }
                }

                // Trajectories v2.2.0 and above methods and properties
                if (IsVerTwoTwo)
                {
                    // GetTimeTillImpact is avalable in Trajectories v2.2.0 and above
                    trGetTimeTillImpact = trajectoriesAPIType.GetMethod("GetTimeTillImpact");
                    if (trGetTimeTillImpact == null)
                    {
                        wrapped = false;
                        return;
                    }
                    trProgradeEntry = trajectoriesAPIType.GetProperty("ProgradeEntry");
                    if (trProgradeEntry == null)
                    {
                        wrapped = false;
                        return;
                    }
                    trRetrogradeEntry = trajectoriesAPIType.GetProperty("RetrogradeEntry");
                    if (trRetrogradeEntry == null)
                    {
                        wrapped = false;
                        return;
                    }
                }

                wrapped = true;
            }

            // Version checking properties
            public static string getVersion = "";
            public static string GetVersion { get { return getVersion; } private set { getVersion = value; } }
            public static bool isVerTwo = false;
            public static bool IsVerTwo { get { return isVerTwo; } private set { isVerTwo = value; } }
            public static bool isVerTwoTwo = false;
            public static bool IsVerTwoTwo { get { return isVerTwoTwo; } private set { isVerTwoTwo = value; } }

            // Standard methods
            public static Vector3? ImpactVector()
            {
                return (Vector3?)trGetImpactPosition.Invoke(null, new object[] { });
            }

            public static Vector3? CorrectedDirection()
            {
                return (Vector3?)trCorrectedDirection.Invoke(null, new object[] { });
            }

            public static Vector3? PlannedDirection()
            {
                return (Vector3?)trPlannedDirection.Invoke(null, new object[] { });
            }

            public static void SetTarget(double lat, double lon, double alt)
            {
                trSetTarget.Invoke(null, new object[] { lat, lon, alt });
            }

            // Trajectories v2.0.0 HasTarget method
            public static bool? HasTarget()
            {
                if (trHasTarget == null)
                    return null;
                return (bool?)trHasTarget.Invoke(null, new object[] { });
            }

            // Trajectories v2.2.0 and above methods and properties
            public static double? GetTimeTillImpact()
            {
                if (trGetTimeTillImpact == null)
                    return null;
                return (double?)trGetTimeTillImpact.Invoke(null, new object[] { });
            }

            public static bool? ProgradeEntry
            {
                get
                {
                    if (trProgradeEntry == null) // will be null if TR version too low.
                        return null;
                    return (bool?)trProgradeEntry.GetValue(null, null);
                }
                set
                {
                    if (trProgradeEntry != null) // will be null if TR version too low.
                        trProgradeEntry.SetValue(null, true, null);
                }
            }

            public static bool? RetrogradeEntry
            {
                get
                {
                    if (trRetrogradeEntry == null) // will be null if TR version too low.
                        return null;
                    return (bool?)trRetrogradeEntry.GetValue(null, null);
                }
                set
                {
                    if (trRetrogradeEntry != null) // will be null if TR version too low.
                        trRetrogradeEntry.SetValue(null, true, null);
                }
            }

            public static bool Wrapped()
            {
                if (wrapped != null)
                {
                    return (bool)wrapped;
                }
                else //if wrapped == null
                {
                    init();
                    return (bool)wrapped;
                }
            }
        }
}
