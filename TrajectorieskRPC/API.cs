using System;
using System.Collections.Generic;
using KRPC.Service;
using KRPC.Service.Attributes;
using UnityEngine;

namespace KRPC.Trajectories
{
    [KRPCService(Name = "Trajectories", GameScene = GameScene.Flight)]
    public static class Service
    {
        [KRPCProcedure]
        public static KRPC.Utils.Tuple<Double, Double> ImpactPos()
        {
            if (Available())
            {
                CelestialBody body = FlightGlobals.ActiveVessel.orbit.referenceBody;
                Vector3? impactVect = TRWrapper.ImpactVector();
                if (impactVect != null)
                {
                    var worldImpactPos = (Vector3d)impactVect + body.position;
                    var lat = body.GetLatitude(worldImpactPos);
                    var lng = DegreeFix(body.GetLongitude(worldImpactPos), -180);
                    return new KRPC.Utils.Tuple<Double, Double>(lat, lng);
                }
                throw new Exception("Impact position is not available. Remember to check addons:tr:HasImpact");
            }
            throw new Exception("Trajectories is not available");
        }

        [KRPCProcedure]
        public static Double GetImpactTime()
        {
            if (Available())
            {
                if (TRWrapper.GetTimeTillImpact() != null)
                {
                    return (double)TRWrapper.GetTimeTillImpact();
                }
                throw new Exception("Impact time is not available. Remember to check addons:tr:HasImpact");
            }
            throw new Exception("Trajectories is not available");
        }

        [KRPCProcedure]
        public static bool HasImpact()
        {
            if (Available())
            {
                return TRWrapper.ImpactVector().HasValue;
            }
            throw new Exception("Trajectories is not available");
        }

        public static bool Available()
        {
            return (bool)TRWrapper.wrapped;
        }

        public static double DegreeFix(double inAngle, double rangeStart)
        {
            double rangeEnd = rangeStart + 360.0;
            double outAngle = inAngle;
            while (outAngle > rangeEnd)
                outAngle -= 360.0;
            while (outAngle < rangeStart)
                outAngle += 360.0;
            return outAngle;
        }
    }
}
