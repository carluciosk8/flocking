/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __BOID_H__
#define __BOID_H__


#include "../Engine/Gfx/SimulationObject.h"
#include "../Engine/Gfx/Terrain.h"
#include "LeaderBoid.h"

#include <list>

using std::list;


//class LeaderBoid;

class Boid : public SimulationObject
{
    public:
        Boid(const char* cpName);
        Boid(const char* cpName, const float3& vfPos, const float3& vfVel);
        virtual ~Boid();

        virtual void update(float dt);

        static list<Boid*>& getBoidsList() { return m_BoidsList; }
        static void setLeader(LeaderBoid* opLeader) { m_opLeaderBoid = opLeader; }

    protected:
        void seeBoids();
        void accumulateSeparationInfluence();
        void accumulateAlignmentInfluence();
        void accumulateCohesionInfluence();
        void accumulateGoalInfluence();
        //void accumulateCruisingInfluence();
        void avoidGround();

        void updateOrientation();


    protected:
		float  MaxSpeed;
		float  MaxSpeedSqr;
		float  MaxChange;
		float  MaxChangeSqr;

		float3  m_vOldPosition;
        float3  m_vOldVelocity;
        float3  m_vAcc;
        float  m_fSpeedSqr;
        float  m_fPerceptionRadiusSqr;
        Boid*  m_opNearestBoid;
        float  m_fNearestBoidDistanceSqr;

        list<Boid*>  m_BoidsSeenList;


    private:
        static list<Boid*>  m_BoidsList;
        static LeaderBoid*  m_opLeaderBoid;
        static Terrain*  s_opTerrain;
		static float3  s_vFlockCenter;
		static float3  s_vFlockVelocity;


    public:
		static void calcFlockCenter();
        static inline float3& getFlockCenter() { return s_vFlockCenter; }
        static inline float3& getFlockVelocity() { return s_vFlockVelocity; }
        static inline void setTerrain(Terrain* opTerrain) { s_opTerrain = opTerrain; }

		static float  s_Ks;
		static float  s_Ka;
		static float  s_Kc;
		static float  s_Kg;
		static float  s_DKs;
		static float  s_DKa;
		static float  s_DKc;
		static float  s_DKg;
};


#endif
