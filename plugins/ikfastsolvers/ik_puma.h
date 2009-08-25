/// autogenerated analytical inverse kinematics code from ikfast program
/// \author Rosen Diankov
///
/// To compile with gcc use: gcc -lstdc++ 
/// To compile without any main function use: gcc -lstdc++ -DIKFAST_NO_MAIN
#include <math.h>
#include <assert.h>
#include <vector>
#include <float.h>

#define IK2PI  6.28318530717959
#define IKPI  3.14159265358979
#define IKPI_2  1.57079632679490

#ifdef _MSC_VER
#ifndef isnan
#define isnan _isnan
#endif
#endif // _MSC_VER

typedef double IKReal;
class IKSolution
{
public:
    /// Gets a solution given its free parameters
    /// \param pfree The free parameters required, range is in [-pi,pi]
    void GetSolution(IKReal* psolution, const IKReal* pfree) const {
        for(size_t i = 0; i < basesol.size(); ++i) {
            if( basesol[i].freeind < 0 )
                psolution[i] = basesol[i].foffset;
            else {
                assert(pfree != NULL);
                psolution[i] = pfree[basesol[i].freeind]*basesol[i].fmul + basesol[i].foffset;
                if( psolution[i] > IKPI )
                    psolution[i] -= IK2PI;
                else if( psolution[i] < -IKPI )
                    psolution[i] += IK2PI;
            }
        }
    }

    /// Gets the free parameters the solution requires to be set before a full solution can be returned
    /// \return vector of indices indicating the free parameters
    const std::vector<int>& GetFree() const { return vfree; }

    struct VARIABLE
    {
        VARIABLE() : freeind(-1), fmul(0), foffset(0) {}
        VARIABLE(int freeind, IKReal fmul, IKReal foffset) : freeind(freeind), fmul(fmul), foffset(foffset) {}
        int freeind;
        IKReal fmul, foffset; ///< joint value is fmul*sol[freeind]+foffset
    };

    std::vector<VARIABLE> basesol;       ///< solution and their offsets if joints are mimiced
    std::vector<int> vfree;
};

inline float IKabs(float f) { return fabsf(f); }
inline double IKabs(double f) { return fabs(f); }

inline float IKasin(float f)
{
assert( f > -1.001f && f < 1.001f ); // any more error implies something is wrong with the solver
if( f <= -1 ) return -IKPI_2;
else if( f >= 1 ) return IKPI_2;
return asinf(f);
}
inline double IKasin(double f)
{
assert( f > -1.001 && f < 1.001 ); // any more error implies something is wrong with the solver
if( f <= -1 ) return -IKPI_2;
else if( f >= 1 ) return IKPI_2;
return asin(f);
}

inline float IKacos(float f)
{
assert( f > -1.001f && f < 1.001f ); // any more error implies something is wrong with the solver
if( f <= -1 ) return IKPI;
else if( f >= 1 ) return 0.0f;
return acosf(f);
}
inline double IKacos(double f)
{
assert( f > -1.001 && f < 1.001 ); // any more error implies something is wrong with the solver
if( f <= -1 ) return IKPI;
else if( f >= 1 ) return 0.0;
return acos(f);
}
inline float IKsin(float f) { return sinf(f); }
inline double IKsin(double f) { return sin(f); }
inline float IKcos(float f) { return cosf(f); }
inline double IKcos(double f) { return cos(f); }
inline float IKsqrt(float f) { if( f <= 0.0f ) return 0.0f; return sqrtf(f); }
inline double IKsqrt(double f) { if( f <= 0.0 ) return 0.0; return sqrt(f); }
inline float IKatan2(float fy, float fx) {
    if( isnan(fy) ) {
        assert(!isnan(fx)); // if both are nan, probably wrong value will be returned
        return IKPI_2;
    }
    else if( isnan(fx) )
        return 0;
    return atan2f(fy,fx);
}
inline double IKatan2(double fy, double fx) {
    if( isnan(fy) ) {
        assert(!isnan(fx)); // if both are nan, probably wrong value will be returned
        return IKPI_2;
    }
    else if( isnan(fx) )
        return 0;
    return atan2(fy,fx);
}
int getNumFreeParameters() { return 0; }
int* getFreeParameters() { return NULL; }
int getNumJoints() { return 6; }

int getIKRealSize() { return sizeof(IKReal); }

/// solves the inverse kinematics equations.
/// \param pfree is an array specifying the free joints of the chain.
bool ik(const IKReal* eetrans, const IKReal* eerot, const IKReal* pfree, std::vector<IKSolution>& vsolutions) {
for(int dummyiter = 0; dummyiter < 1; ++dummyiter) {
    vsolutions.resize(0); vsolutions.reserve(8);
    IKReal j0, cj0, sj0,
    j1, cj1, sj1,
    j2, cj2, sj2,
    j3, cj3, sj3,
    j4, cj4, sj4,
    j5, cj5, sj5,
    _r00, r00 = eerot[0*3+0],
    _r01, r01 = eerot[0*3+1],
    _r02, r02 = eerot[0*3+2],
    _r10, r10 = eerot[1*3+0],
    _r11, r11 = eerot[1*3+1],
    _r12, r12 = eerot[1*3+2],
    _r20, r20 = eerot[2*3+0],
    _r21, r21 = eerot[2*3+1],
    _r22, r22 = eerot[2*3+2],
    _px, _py, _pz, px = eetrans[0], py = eetrans[1], pz = eetrans[2];
    
    _r00=r00;
    _r01=r01;
    _r02=r02;
    _px=px;
    _r10=r10;
    _r11=r11;
    _r12=r12;
    _py=((-1.37100000000000)+(py));
    _r20=r20;
    _r21=r21;
    _r22=r22;
    _pz=pz;
    r00 = _r00; r01 = _r01; r02 = _r02; r10 = _r10; r11 = _r11; r12 = _r12; r20 = _r20; r21 = _r21; r22 = _r22; px = _px; py = _py; pz = _pz;
    {
        if( 1 ) {
        {
            IKReal j0eval[1];
            j0eval[0]=(((px)*(px))+((pz)*(pz)));
            if( IKabs(j0eval[0]) < 0.000010  ) {
                continue;
                
            } else {
                {
                IKReal j0array[2], cj0array[2], sj0array[2];
                bool j0valid[2]={false};
                IKReal x0=((-1.00000000000000)*(pz));
                IKReal x1=((-1.00000000000000)*(px));
                IKReal x2=IKatan2(x0, x1);
                IKReal x3=(px)*(px);
                IKReal x4=(pz)*(pz);
                IKReal x5=((x3)+(x4));
                IKReal x6=((IKabs(x5) != 0)?(pow(x5,-0.500000000000000)):(IKReal)1.0e30);
                IKReal x7=((0.150100000000748)*(x6));
                if( (x7) < -1.0001 || (x7) > 1.0001 )
                    continue;
                IKReal x8=IKasin(x7);
                j0array[0]=((x8)+(((-1.00000000000000)*(x2))));
                sj0array[0]=IKsin(j0array[0]);
                cj0array[0]=IKcos(j0array[0]);
                j0array[1]=((3.14159265358979)+(((-1.00000000000000)*(x2)))+(((-1.00000000000000)*(x8))));
                sj0array[1]=IKsin(j0array[1]);
                cj0array[1]=IKcos(j0array[1]);
                if( j0array[0] > IKPI )
                    j0array[0]-=IK2PI;
                else if( j0array[0] < -IKPI )
                    j0array[0]+=IK2PI;
                j0valid[0] = true;
                if( j0array[1] > IKPI )
                    j0array[1]-=IK2PI;
                else if( j0array[1] < -IKPI )
                    j0array[1]+=IK2PI;
                j0valid[1] = true;
                if( j0valid[0] && j0valid[1] && IKabs(cj0array[0]-cj0array[1]) < 0.0001 && IKabs(sj0array[0]-sj0array[1]) < 0.0001 )
                    j0valid[1]=false;
                for(int ij0 = 0; ij0 < 2; ++ij0) {
                if( !j0valid[ij0] )
                    continue;
                j0 = j0array[ij0]; cj0 = cj0array[ij0]; sj0 = sj0array[ij0];
                
                {
                IKReal j2array[2], cj2array[2], sj2array[2];
                bool j2valid[2]={false};
                IKReal x9=(py)*(py);
                IKReal x10=((2.67068488904624)*(x9));
                IKReal x11=x3;
                IKReal x12=((2.67068488904624)*(x11));
                IKReal x13=x4;
                IKReal x14=((2.67068488904624)*(x13));
                IKReal x15=((x10)+(x12)+(x14));
                IKReal x16=((1.06017897617130)+(((-1.00000000000000)*(x15))));
                if( (x16) < -1.0001 || (x16) > 1.0001 )
                    continue;
                IKReal x17=IKasin(x16);
                j2array[0]=((0.0468371131133505)+(((-1.00000000000000)*(x17))));
                sj2array[0]=IKsin(j2array[0]);
                cj2array[0]=IKcos(j2array[0]);
                j2array[1]=((3.18842976670314)+(x17));
                sj2array[1]=IKsin(j2array[1]);
                cj2array[1]=IKcos(j2array[1]);
                if( j2array[0] > IKPI )
                    j2array[0]-=IK2PI;
                else if( j2array[0] < -IKPI )
                    j2array[0]+=IK2PI;
                j2valid[0] = true;
                if( j2array[1] > IKPI )
                    j2array[1]-=IK2PI;
                else if( j2array[1] < -IKPI )
                    j2array[1]+=IK2PI;
                j2valid[1] = true;
                if( j2valid[0] && j2valid[1] && IKabs(cj2array[0]-cj2array[1]) < 0.0001 && IKabs(sj2array[0]-sj2array[1]) < 0.0001 )
                    j2valid[1]=false;
                for(int ij2 = 0; ij2 < 2; ++ij2) {
                if( !j2valid[ij2] )
                    continue;
                j2 = j2array[ij2]; cj2 = cj2array[ij2]; sj2 = sj2array[ij2];
                
                {
                IKReal j1array[1], cj1array[1], sj1array[1];
                bool j1valid[1]={false};
                IKReal x18=((2.00000000000000)*(cj0)*(px)*(pz)*(sj0));
                IKReal x19=(cj0)*(cj0);
                IKReal x20=x3;
                IKReal x21=((x19)*(x20));
                IKReal x22=x4;
                IKReal x23=(sj0)*(sj0);
                IKReal x24=((x22)*(x23));
                IKReal x25=x9;
                IKReal x26=((x24)+(x25)+(x21));
                IKReal x27=((x18)+(((-1.00000000000000)*(x26))));
                IKReal x28=((IKabs(x27) != 0)?((IKReal)1/(x27)):(IKReal)1.0e30);
                j1array[0]=IKatan2(((((-0.0202999999999065)*(cj0)*(px)*(sj2)*(x28)))+(((-0.433099999998376)*(cj0)*(cj2)*(px)*(x28)))+(((0.433099999998376)*(cj2)*(pz)*(sj0)*(x28)))+(((0.433099999998376)*(py)*(sj2)*(x28)))+(((-0.0202999999999065)*(cj2)*(py)*(x28)))+(((0.0202999999999065)*(pz)*(sj0)*(sj2)*(x28)))+(((0.431799999998475)*(py)*(x28)))), ((((-0.431799999998475)*(cj0)*(px)*(x28)))+(((-0.433099999998376)*(cj0)*(px)*(sj2)*(x28)))+(((0.0202999999999065)*(cj0)*(cj2)*(px)*(x28)))+(((0.433099999998376)*(pz)*(sj0)*(sj2)*(x28)))+(((-0.0202999999999065)*(cj2)*(pz)*(sj0)*(x28)))+(((-0.0202999999999065)*(py)*(sj2)*(x28)))+(((-0.433099999998376)*(cj2)*(py)*(x28)))+(((0.431799999998475)*(pz)*(sj0)*(x28)))));
                sj1array[0]=IKsin(j1array[0]);
                cj1array[0]=IKcos(j1array[0]);
                if( j1array[0] > IKPI )
                    j1array[0]-=IK2PI;
                else if( j1array[0] < -IKPI )
                    j1array[0]+=IK2PI;
                j1valid[0] = true;
                { int ij1 = 0;
                if( !j1valid[ij1] )
                    continue;
                j1 = j1array[0]; cj1 = cj1array[0]; sj1 = sj1array[0];
                
                _r00=((((-1.00000000000000)*(cj0)*(r00)*(sj1)*(sj2)))+(((-1.00000000000000)*(cj2)*(r10)*(sj1)))+(((r20)*(sj0)*(sj1)*(sj2)))+(((-1.00000000000000)*(cj1)*(r10)*(sj2)))+(((cj0)*(cj1)*(cj2)*(r00)))+(((-1.00000000000000)*(cj1)*(cj2)*(r20)*(sj0))));
                _r01=((((-1.00000000000000)*(cj1)*(cj2)*(r21)*(sj0)))+(((-1.00000000000000)*(cj1)*(r11)*(sj2)))+(((r21)*(sj0)*(sj1)*(sj2)))+(((-1.00000000000000)*(cj0)*(r01)*(sj1)*(sj2)))+(((-1.00000000000000)*(cj2)*(r11)*(sj1)))+(((cj0)*(cj1)*(cj2)*(r01))));
                _r02=((((cj0)*(cj1)*(cj2)*(r02)))+(((r22)*(sj0)*(sj1)*(sj2)))+(((-1.00000000000000)*(cj1)*(r12)*(sj2)))+(((-1.00000000000000)*(cj2)*(r12)*(sj1)))+(((-1.00000000000000)*(cj1)*(cj2)*(r22)*(sj0)))+(((-1.00000000000000)*(cj0)*(r02)*(sj1)*(sj2))));
                _r10=((((cj0)*(cj2)*(r00)*(sj1)))+(((cj1)*(cj2)*(r10)))+(((-1.00000000000000)*(r10)*(sj1)*(sj2)))+(((cj0)*(cj1)*(r00)*(sj2)))+(((-1.00000000000000)*(cj1)*(r20)*(sj0)*(sj2)))+(((-1.00000000000000)*(cj2)*(r20)*(sj0)*(sj1))));
                _r11=((((-1.00000000000000)*(r11)*(sj1)*(sj2)))+(((cj0)*(cj1)*(r01)*(sj2)))+(((-1.00000000000000)*(cj1)*(r21)*(sj0)*(sj2)))+(((-1.00000000000000)*(cj2)*(r21)*(sj0)*(sj1)))+(((cj1)*(cj2)*(r11)))+(((cj0)*(cj2)*(r01)*(sj1))));
                _r12=((((cj0)*(cj1)*(r02)*(sj2)))+(((-1.00000000000000)*(cj1)*(r22)*(sj0)*(sj2)))+(((-1.00000000000000)*(r12)*(sj1)*(sj2)))+(((cj1)*(cj2)*(r12)))+(((cj0)*(cj2)*(r02)*(sj1)))+(((-1.00000000000000)*(cj2)*(r22)*(sj0)*(sj1))));
                _r20=((((r00)*(sj0)))+(((cj0)*(r20))));
                _r21=((((cj0)*(r21)))+(((r01)*(sj0))));
                _r22=((((cj0)*(r22)))+(((r02)*(sj0))));
                {
                IKReal j4eval;
                j4eval=_r11;
                if( j4eval >= -1.000010 && j4eval <= -0.999990 ) {
                    {
                    j4 = 3.141593; sj4 = 0.000000; cj4 = -1.000000;
                    IKReal j3mul = 1;
                    j3=0;
                    IKReal j5mul=1.00000000000000;
                    j5=((-1.00000000000000)*(IKatan2(_r02, ((-1.00000000000000)*(_r00)))));
                    vsolutions.push_back(IKSolution()); IKSolution& solution = vsolutions.back();
                    solution.basesol.resize(6);
                    solution.basesol[0].foffset = j0;
                    solution.basesol[1].foffset = j1;
                    solution.basesol[2].foffset = j2;
                    solution.basesol[3].foffset = j3;
                    solution.basesol[3].fmul = j3mul;
                    solution.basesol[3].freeind = 0;
                    solution.basesol[4].foffset = j4;
                    solution.basesol[5].foffset = j5;
                    solution.basesol[5].fmul = j5mul;
                    solution.basesol[5].freeind = 0;
                    solution.vfree.resize(1);
                    solution.vfree[0] = 3;
                    }
                    }
                else if( j4eval >= 0.999990 && j4eval <= 1.000010 ) {
                    {
                    j4 = 0.000000; sj4 = 0.000000; cj4 = 1.000000;
                    IKReal j3mul = 1;
                    j3=0;
                    IKReal j5mul=-1.00000000000000;
                    j5=((((-1.00000000000000)*(IKatan2(_r02, ((-1.00000000000000)*(_r00))))))+(((-1.00000000000000)*(3.14159265358979))));
                    vsolutions.push_back(IKSolution()); IKSolution& solution = vsolutions.back();
                    solution.basesol.resize(6);
                    solution.basesol[0].foffset = j0;
                    solution.basesol[1].foffset = j1;
                    solution.basesol[2].foffset = j2;
                    solution.basesol[3].foffset = j3;
                    solution.basesol[3].fmul = j3mul;
                    solution.basesol[3].freeind = 0;
                    solution.basesol[4].foffset = j4;
                    solution.basesol[5].foffset = j5;
                    solution.basesol[5].fmul = j5mul;
                    solution.basesol[5].freeind = 0;
                    solution.vfree.resize(1);
                    solution.vfree[0] = 3;
                    }
                    }
                else {
                    {
                    IKReal j3array[2], cj3array[2], sj3array[2];
                    bool j3valid[2]={false};
                    j3array[0]=IKatan2(((-1.00000000000000)*(_r21)), _r01);
                    sj3array[0]=IKsin(j3array[0]);
                    cj3array[0]=IKcos(j3array[0]);
                    j3array[1] = j3array[0] > 0 ? j3array[0]-IKPI : j3array[0]+IKPI;
                    sj3array[1] = -sj3array[0];
                    cj3array[1] = -cj3array[0];
                    if( j3array[0] > IKPI )
                        j3array[0]-=IK2PI;
                    else if( j3array[0] < -IKPI )
                        j3array[0]+=IK2PI;
                    j3valid[0] = true;
                    if( j3array[1] > IKPI )
                        j3array[1]-=IK2PI;
                    else if( j3array[1] < -IKPI )
                        j3array[1]+=IK2PI;
                    j3valid[1] = true;
                    if( j3valid[0] && j3valid[1] && IKabs(cj3array[0]-cj3array[1]) < 0.0001 && IKabs(sj3array[0]-sj3array[1]) < 0.0001 )
                        j3valid[1]=false;
                    for(int ij3 = 0; ij3 < 2; ++ij3) {
                    if( !j3valid[ij3] )
                        continue;
                    j3 = j3array[ij3]; cj3 = cj3array[ij3]; sj3 = sj3array[ij3];
                    
                    {
                    IKReal evalcond;
                        evalcond=IKcos(j3);
                        if( IKabs(evalcond) < 0.00001 ) {
                        {
                        IKReal j5array[1], cj5array[1], sj5array[1];
                        bool j5valid[1]={false};
                        IKReal x29=IKsin(j3);
                        IKReal x30=((IKabs(x29) != 0)?((IKReal)1/(x29)):(IKReal)1.0e30);
                        j5array[0]=IKatan2(((-1.00000000000000)*(_r00)*(x30)), ((_r02)*(x30)));
                        sj5array[0]=IKsin(j5array[0]);
                        cj5array[0]=IKcos(j5array[0]);
                        if( j5array[0] > IKPI )
                            j5array[0]-=IK2PI;
                        else if( j5array[0] < -IKPI )
                            j5array[0]+=IK2PI;
                        j5valid[0] = true;
                        { int ij5 = 0;
                        if( !j5valid[ij5] )
                            continue;
                        j5 = j5array[0]; cj5 = cj5array[0]; sj5 = sj5array[0];
                        
                        {
                        IKReal j4array[1], cj4array[1], sj4array[1];
                        bool j4valid[1]={false};
                        j4array[0]=IKatan2(((-1.00000000000000)*(_r21)*(((IKabs(IKsin(j3)) != 0)?((IKReal)1/(IKsin(j3))):(IKReal)1.0e30))), _r11);
                        sj4array[0]=IKsin(j4array[0]);
                        cj4array[0]=IKcos(j4array[0]);
                        if( j4array[0] > IKPI )
                            j4array[0]-=IK2PI;
                        else if( j4array[0] < -IKPI )
                            j4array[0]+=IK2PI;
                        j4valid[0] = true;
                        { int ij4 = 0;
                        if( !j4valid[ij4] )
                            continue;
                        j4 = j4array[0]; cj4 = cj4array[0]; sj4 = sj4array[0];
                        
                        vsolutions.push_back(IKSolution()); IKSolution& solution = vsolutions.back();
                        solution.basesol.resize(6);
                        solution.basesol[0].foffset = j0;
                        solution.basesol[1].foffset = j1;
                        solution.basesol[2].foffset = j2;
                        solution.basesol[3].foffset = j3;
                        solution.basesol[4].foffset = j4;
                        solution.basesol[5].foffset = j5;
                        solution.vfree.resize(0);
                        }
                        }
                        }
                        }
                        } else {
                        if( 1 ) {
                        {
                        IKReal j4array[1], cj4array[1], sj4array[1];
                        bool j4valid[1]={false};
                        j4array[0]=IKatan2(((_r01)*(((IKabs(cj3) != 0)?((IKReal)1/(cj3)):(IKReal)1.0e30))), _r11);
                        sj4array[0]=IKsin(j4array[0]);
                        cj4array[0]=IKcos(j4array[0]);
                        if( j4array[0] > IKPI )
                            j4array[0]-=IK2PI;
                        else if( j4array[0] < -IKPI )
                            j4array[0]+=IK2PI;
                        j4valid[0] = true;
                        { int ij4 = 0;
                        if( !j4valid[ij4] )
                            continue;
                        j4 = j4array[0]; cj4 = cj4array[0]; sj4 = sj4array[0];
                        
                        {
                        IKReal evalcond;
                            evalcond=IKsin(j4);
                            if( IKabs(evalcond) < 0.00001 ) {
                            {
                            IKReal j5array[1], cj5array[1], sj5array[1];
                            bool j5valid[1]={false};
                            IKReal x31=IKsin(j4);
                            IKReal x32=((IKabs(x31) != 0)?(pow(x31,-2.00000000000000)):(IKReal)1.0e30);
                            IKReal x33=IKcos(j3);
                            IKReal x34=(x33)*(x33);
                            IKReal x35=((x34)+(((-1.00000000000000)*(x32))));
                            IKReal x36=((IKabs(x35) != 0)?((IKReal)1/(x35)):(IKReal)1.0e30);
                            IKReal x37=IKsin(j3);
                            IKReal x38=IKcos(j4);
                            j5array[0]=IKatan2(((((_r00)*(x32)*(x36)*(x37)))+(((-1.00000000000000)*(_r02)*(x32)*(x33)*(x36)*(x38)))), ((((-1.00000000000000)*(_r00)*(x32)*(x33)*(x36)*(x38)))+(((-1.00000000000000)*(_r02)*(x32)*(x36)*(x37)))));
                            sj5array[0]=IKsin(j5array[0]);
                            cj5array[0]=IKcos(j5array[0]);
                            if( j5array[0] > IKPI )
                                j5array[0]-=IK2PI;
                            else if( j5array[0] < -IKPI )
                                j5array[0]+=IK2PI;
                            j5valid[0] = true;
                            { int ij5 = 0;
                            if( !j5valid[ij5] )
                                continue;
                            j5 = j5array[0]; cj5 = cj5array[0]; sj5 = sj5array[0];
                            
                            vsolutions.push_back(IKSolution()); IKSolution& solution = vsolutions.back();
                            solution.basesol.resize(6);
                            solution.basesol[0].foffset = j0;
                            solution.basesol[1].foffset = j1;
                            solution.basesol[2].foffset = j2;
                            solution.basesol[3].foffset = j3;
                            solution.basesol[4].foffset = j4;
                            solution.basesol[5].foffset = j5;
                            solution.vfree.resize(0);
                            }
                            }
                            } else {
                            if( 1 ) {
                            {
                            IKReal j5array[1], cj5array[1], sj5array[1];
                            bool j5valid[1]={false};
                            IKReal x39=IKsin(j4);
                            IKReal x40=((IKabs(x39) != 0)?(pow(x39,-2.00000000000000)):(IKReal)1.0e30);
                            IKReal x41=IKcos(j3);
                            IKReal x42=(x41)*(x41);
                            IKReal x43=((x42)+(((-1.00000000000000)*(x40))));
                            IKReal x44=((IKabs(x43) != 0)?((IKReal)1/(x43)):(IKReal)1.0e30);
                            IKReal x45=IKsin(j3);
                            IKReal x46=IKcos(j4);
                            j5array[0]=IKatan2(((((-1.00000000000000)*(_r02)*(x40)*(x41)*(x44)*(x46)))+(((_r00)*(x40)*(x44)*(x45)))), ((((-1.00000000000000)*(_r02)*(x40)*(x44)*(x45)))+(((-1.00000000000000)*(_r00)*(x40)*(x41)*(x44)*(x46)))));
                            sj5array[0]=IKsin(j5array[0]);
                            cj5array[0]=IKcos(j5array[0]);
                            if( j5array[0] > IKPI )
                                j5array[0]-=IK2PI;
                            else if( j5array[0] < -IKPI )
                                j5array[0]+=IK2PI;
                            j5valid[0] = true;
                            { int ij5 = 0;
                            if( !j5valid[ij5] )
                                continue;
                            j5 = j5array[0]; cj5 = cj5array[0]; sj5 = sj5array[0];
                            
                            vsolutions.push_back(IKSolution()); IKSolution& solution = vsolutions.back();
                            solution.basesol.resize(6);
                            solution.basesol[0].foffset = j0;
                            solution.basesol[1].foffset = j1;
                            solution.basesol[2].foffset = j2;
                            solution.basesol[3].foffset = j3;
                            solution.basesol[4].foffset = j4;
                            solution.basesol[5].foffset = j5;
                            solution.vfree.resize(0);
                            }
                            }
                            } else {
                        }
                        }
                        }
                        }
                        }
                        } else {
                    }
                    }
                    }
                    }
                    }
                    }
                }
                }
                }
                }
                }
                }
                }
                
            }
            }
        } else {
    }
    }
    }
return vsolutions.size()>0;
}

#ifndef IKFAST_NO_MAIN
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if( argc != 12+getNumFreeParameters()+1 ) {
        printf("\nUsage: ./ik r00 r01 r02 t0 r10 r11 r12 t1 r20 r21 r22 t2 free0 ...\n\n"
               "Returns the ik solutions given the transformation of the end effector specified by\n"
               "a 3x3 rotation R (rXX), and a 3x1 translation (tX).\n"
               "There are %d free parameters that have to be specified.\n\n",getNumFreeParameters());
        return 1;
    }

    std::vector<IKSolution> vsolutions;
    std::vector<IKReal> vfree(getNumFreeParameters());
    IKReal eerot[9],eetrans[3];
    eerot[0] = atof(argv[1]); eerot[1] = atof(argv[2]); eerot[2] = atof(argv[3]); eetrans[0] = atof(argv[4]);
    eerot[3] = atof(argv[5]); eerot[4] = atof(argv[6]); eerot[5] = atof(argv[7]); eetrans[1] = atof(argv[8]);
    eerot[6] = atof(argv[9]); eerot[7] = atof(argv[10]); eerot[8] = atof(argv[11]); eetrans[2] = atof(argv[12]);
    for(size_t i = 0; i < vfree.size(); ++i)
        vfree[i] = atof(argv[13+i]);
    bool bSuccess = ik(eetrans, eerot, vfree.size() > 0 ? &vfree[0] : NULL, vsolutions);

    if( !bSuccess ) {
        fprintf(stderr,"Failed to get ik solution\n");
        return -1;
    }

    printf("Found %d ik solutions:\n", (int)vsolutions.size());
    std::vector<IKReal> sol(getNumJoints());
    for(size_t i = 0; i < vsolutions.size(); ++i) {
        printf("sol%d (free=%d): ", (int)i, (int)vsolutions[i].GetFree().size());
        std::vector<IKReal> vsolfree(vsolutions[i].GetFree().size());
        vsolutions[i].GetSolution(&sol[0],vsolfree.size()>0?&vsolfree[0]:NULL);
        for( size_t j = 0; j < sol.size(); ++j)
            printf("%f, ", (float)sol[j]);
        printf("\n");
    }
    return 0;
}

#endif
