/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
	Atmosphere code adapted from: (c) 2002 Nathaniel Hoffman,
	Kenneth J. Mitchell and Arcot J. Preetham
 ***************************************************************************/
#ifndef __ATMOSPHERE_H__
#define __ATMOSPHERE_H__

#include <stdio.h>

#include "../Engine/Math/Vector3.h"

// Various Atmosphere parameters.
typedef enum {
	eAtmBetaRayMultiplier,
	eAtmBetaMieMultiplier,
	eAtmInscatteringMultiplier,
	eAtmExtinctionMultiplier,
	eAtmHGg,
} AtmosphereParams;


class Atmosphere {

public:
	Atmosphere();
	~Atmosphere() {};

	void SetParam(AtmosphereParams param, float fValue);
	float GetParam(AtmosphereParams param);

    float GetHGg() {return m_fHGg;};
    float3 GetBetaRayleigh() {return m_vBetaRay;};
    float3 GetBetaDashRayleigh() {return m_vBetaDashRay;};

    float3 GetBetaMie() {return m_vBetaMie;};
    float3 GetBetaDashMie() {return m_vBetaDashMie;};

	void Interpolate(Atmosphere *one, Atmosphere *two, float f);

	void Dump2(FILE *f);
	void Read2(FILE *f);
	void Finalize() {};

	Atmosphere operator + ( const Atmosphere&) const;
    Atmosphere operator * ( float ) const;
    friend Atmosphere operator * ( float , const Atmosphere& );




private:
	float m_fHGg;		// g value in Henyey Greenstein approximation function.

	// Ideally, the following multipliers should all be 1.0, but provided here for study.
	// The final color of an object in atmosphere is sum of inscattering term and extinction term.
	float m_fInscatteringMultiplier;	// Multiply inscattering term with this factor.
	float m_fExtinctionMultiplier;		// Multiply extinction term with this factor.
	float m_fBetaRayMultiplier;			// Multiply  Rayleigh scattering coefficient with this factor
	float m_fBetaMieMultiplier;			// Multiply  Mie scattering coefficient with this factor

    float3 m_vBetaRay;				// Rayleigh scattering coeff
    float3 m_vBetaDashRay;			// Rayleigh Angular scattering coeff without phase term.
    float3 m_vBetaMie;				// Mie scattering coeff
    float3 m_vBetaDashMie;			// Mie Angular scattering coeff without phase term.

	void CalculateScatteringConstants();


};

Atmosphere operator * ( float , const Atmosphere& );

#endif
