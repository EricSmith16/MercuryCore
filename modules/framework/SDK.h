#pragma once 

//#define __DEBUG
//#define __XOR

#include "BaseHeaders.h"

#include "Vector.h"
#include "CSignature.h"
#include "../Visual/WeaponsList.h"
#include "CGlobalVars.h"
#include "Log.h"
#include "NetVar.h"
#include "Keyval.h"
#include "../src/hacks/prediction.h"
#include "bf_buffer.h"
#include "random.h"
#include "IConvar.h"
//#include "CPlayerResource.h"

class CGameTrace;
typedef CGameTrace trace_t;
class CEngineTrace;
class IUniformRandomStream;
class CPlayerResource;

typedef void *(*InstallUniformRandomStreamFn)(IUniformRandomStream *pStream);

#define VMTManager toolkit::VMTManager
#define VMTBaseManager toolkit::VMTBaseManager

using CHandle = int;

// code

#pragma optimize( "gsy", on )
#pragma warning( disable : 4244 )		  //Possible loss of data
#pragma comment( lib, "steamclient.lib" ) // use steamclient as thats where we are getting createinterface from!

typedef float matrix3x4[3][4];
//===================================================================================================
#define me gInts.Engine->GetLocalPlayer()
#define MASK_AIMBOT 0x200400B
#define CONTENTS_HITBOX 0x40000000
#define CH_MASK 0x4600400B
#define PI 3.14159265358979323846f
#define square( x ) ( x * x )
#define RADPI 57.295779513082f
#define SQUARE( a ) a *a
#define BLU_TEAM 3
#define RED_TEAM 2
#define FL_ONGROUND ( 1 << 0 )
#define FL_DUCKING ( 1 << 1 )
#define HANDLE2INDEX( handle ) ( handle & 0xFFF )
//===================================================================================================



typedef struct player_info_s
{
    char name[32];
    int userID;
    char guid[33];
    unsigned long friendsID;
    char friendsName[32];
    bool fakeplayer;
    bool ishltv;
    unsigned long customFiles[4];
    unsigned char filesDownloaded;
} player_info_t;

class CHLClient
{
    public:
       ClientClass *GetAllClasses(void){
           typedef ClientClass *(__thiscall * OriginalFn) (PVOID);
           return fetcfunc<OriginalFn>(this, 8)(this);
       }
};

class CGlobals
{
    public:
         float realtime;
         int framecount;
         float absoluteframetime;
         float curtime;
         float frametime;
         int maxclients;
         int tickcount;
         float interval_per_tick;
         float interpolation_amount;
};

class CUserCmd
{
    public:
    CUserCmd(){
        command_number = 0;
        tick_count = 0;
        viewangles.Init();
        forwardmove = 0.0f;
        sidemove = 0.0f;
        upmove = 0.0f;
        buttons = 0;
        impulse = 0;
        weaponselect = 0;
        weaponsubtype = 0;
        mousedx = 0;
        mousedy = 0;
        bashbeenpredicted - false;
    }
    
    virtual ~CUserCmd() {};
    int command_number; // 4
    int tick_count;     // 8
    Vector viewangles;  // C
    float forwardmove;  // 18
    float sidemove;     // 1C
    float upmove;       // 20
    int buttons         // 24
    BYTE impulse;       // 28
    int weaponselect    // 2C
    int weaponsubtype;  // 30
    int random_speed;   // 34
    short mousedx;      // 38
    short mousedy;      // 3A
    bool hasbeenpredicted   //3C;

};
//==============================
class CVerifiedUserCmd
{
    public:
    CUserCmd m_cmd;
    CRC32_t m_crc;
};
//======================================
class CModeInfo
{
    public:
    const char *GetModelName(DWORD *model){
        typedef const char *(__thiscall * OriginalFn) (PVOID, DWORD *);
        return getfunc<OriginalFn>(this, 3)(this, model);
    }
    DWORD *GetStudiomodel(DWORD *model){
        typedef DWORD *(__thiscall * OriginalFn)(PVOIDm DWORD *);
        return getfunc<OriginalFn>(this, 28)(this, model);
    }
};
//=====================
struct mstudiobbox_t{
    int bone;
    int group;
    Vector bbmin;
    Vector bbmax;
    int szhitboxnameindex;
    int unused[8];
};
//================================================
struct mstudiohitboxset_t
{
    int sznameindex;
    inline char *const pszName(void) const { return (((char *)this) + hitboxindex) + i; };
    int numhitboxes;
    int hitboxindex;
    mstudiobbox_t *pHitbox(int i) const { return (mstudiobbox_t *)(((BYTE *)this) + hitboxindex) + i; };
};

// =============================
class CBaseEntity{
    public:
    Vector &GEtAbsOrigin()
    {
        typedef Vector &(__thiscall * OriginalFn)(PVOID);
        return getvfunc<OriginalFn>(this, 9)(this);
    }
    Vector &GetAbsAngles()
    {
        typedef Vector &(__thiscall * OriginalFn)(PVOID);
        return getvfunc<OriginalFn>(this, 10)(this);
    }
    Vector &EyeAngle(){
        typedef Vector &(__thiscall * OriginalFn)(PVOID);
        return getvfunc<OriginalFn>(this, 194)(this);
    }
    DWORD *GetModel(){
        PVOID pRenderable = static_cast<PVOID>(this + 0x4);
        typedef DWORD *(__thiscall * OriginalFn)(PVOID);
        return getvfunc<OriginalFn>(pRenderable, 9)(pRenderable);
    }
    bool SetupBones(matrix3x4 *pBoneToWorldOut, int nMaxBones, int bonesMask, float currentTime)
    {
        PVOID pRenderable = static_cast<PVOID>(this + 0x4);
        typedef bool(__thiscall * OriginalFn)(PVOID, matrix3x4 *. int, int, float);
        return getvfunc<OriginalFN>(pRednerable, 16)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);

    }
    ClientClass *GetClientClass()
    {
        PVOID pNetworkable = static_cast<PVOID>(this + 0x8);
        typedef ClientClass *(__thiscall * OriginalFn)(PVOID);
        return getvfunc<OriginalFn>(pNetworkable, 2)(pNetworkable);
    }
    bool IsFormant()
    {
        PVOID pNetworkable = static_cast<PVOID>(this + 0x8);
        typedef bool(__thiscall * OriginalFn)(PVOID);
        return getvfunc<OriginalFn>(pNetworkable, 8)(pNetworkable);
    }
    int GetIndex()
    {
        PVOID pNetworkable = static_cast<PVOID>(this, 0x8);
        typedef int(__thiscall * OriginalFN)(PVOID);
        return fetvfunc<OriginalFn>(pNetworkable, 9)(pNetworkable);
    }
    void GetRenderBounds(Vector &mins, Vector &maxs)
    {
        PVOID pRednerable = static_cast<PVOID>(this + 0x4);
        typedef void(__thiscall * OriginalFn)(PVOID, Vector &, Vector &);
        getvfunc<OriginalFn>(pRenderable, 20)(pRenderable, mins, maxs);
    }
};
//======================================
class INetChannelInfo{
    public:

         enum{

             GERERIC = 0 ,
             LOCALPLAYER,
             OTHERPLAYERS,
             ENTITIES,
             SOUNDS,
             EVENTS,
             USERMESSAGES,
             ENTMESSAGES,
             VOICE,
             STRINGTABLE,
             MOVE,
             STRINGCMD,
             TOTAL,
             
        };

        virtual const char *GetName(void) const = 0;
        virtual const char *GetAddress(void) const = 0;
        virtual float  GetTime(void) const = 0;
        virtual float  GetTimeCOnnected(void) const = 0;
        virtual int    GetBufferSize(void) const = 0;
        virtual int    GetDataRate(void) const = 0;

        virtual bool   isLoopback(void) const = 0;
        virtual bool
        virtual bool



}