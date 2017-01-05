/**********************************************************************
 Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ********************************************************************/

/**
 \file light.h
 \author Dmitry Kozlov
 \version 1.0
 \brief Contains declaration of various light types supported by the renderer.
 */
#pragma once

#include "math/float3.h"
#include "math/float2.h"
#include <memory>
#include <string>

#include "iterator.h"

namespace Baikal
{
    class Texture;
    
    /**
     \brief Light base interface.
     
     High-level interface all light classes need to implement.
     */
    class Light
    {
    public:
        // Constructor
        Light() = default;
        // Destructor
        virtual ~Light() = 0;
        
        // Get total radiant power (integral)
        //virtual RadeonRays::float3 GetRadiantPower() const = 0;
        
        // Set and get position
        virtual RadeonRays::float3 GetPosition() const;
        virtual void SetPosition(RadeonRays::float3 const& p);
        
        // Set and get direction
        virtual RadeonRays::float3 GetDirection() const;
        virtual void SetDirection(RadeonRays::float3 const& d);
        
        // Set and get direction
        virtual RadeonRays::float3 GetEmittedRadiance() const;
        virtual void SetEmittedRadiance(RadeonRays::float3 const& e);
        
        // Iterate all textures used by the light
        virtual Iterator* CreateTextureIterator() const;
        
        // Forbidden stuff
        Light(Light const&) = delete;
        Light& operator = (Light const&) = delete;
        
    private:
        RadeonRays::float3 m_p;
        RadeonRays::float3 m_d;
        RadeonRays::float3 m_e;
    };
    
    /**
     \brief Simple point light source.
     
     Non-physical light emitting power from a single point in all directions.
     */
    class PointLight: public Light
    {
    public:
    };
    
    /**
     \brief Simple directional light source.
     
     Non-physical light emitting power from a single direction.
     */
    class DirectionalLight: public Light
    {
    public:
    };
    
    /**
     \brief Simple cone-shaped light source.
     
     Non-physical light emitting power from a single point in a cone of directions.
     */
    class SpotLight: public Light
    {
    public:
        // Get and set inner and outer falloff angles: they are set as cosines of angles between light direction
        // and cone opening.
        virtual void SetConeShape(RadeonRays::float2 angles);
        virtual RadeonRays::float2 GetConeShape() const;
        
    private:
        RadeonRays::float2 m_angles;
    };
    
    /**
     \brief Image-based distant light source.
     
     Physical light emitting from all spherical directions.
     */
    class ImageBasedLight: public Light
    {
    public:
        // Get and set illuminant texture
        virtual void SetTexture(Texture const* texture);
        virtual Texture const* GetTexture() const;
        
    private:
        Texture const* m_texture;
    };
    
    // Area light
    class AreaLight: public Light
    {
    public:
        // Get parent shape
        virtual Shape const* GetShape() const;
        // Get parent prim idx
        virtual std::size_t GetPrimitiveIdx() const;
        
    private:
        Shape const* m_shape;
        std::size_t m_prim_idx;
    };

    inline Light::~Light()
    {
        
    }
    
    inline RadeonRays::float3 Light::GetPosition() const
    {
        return m_p;
    }
    
    inline void Light::SetPosition(RadeonRays::float3 const& p)
    {
        m_p = p;
    }
    
    inline RadeonRays::float3 Light::GetDirection() const
    {
        return m_d;
    }
    
    inline void Light::SetDirection(RadeonRays::float3 const& d)
    {
        m_d = d;
    }
    
    inline Iterator* Light::CreateTextureIterator() const
    {
        return new EmptyIterator();
    }
    
    inline RadeonRays::float3 Light::GetEmittedRadiance() const
    {
        return m_e;
    }
    
    inline void Light::SetEmittedRadiance(RadeonRays::float3 const& e)
    {
        m_e = e;
    }
    
    inline void SpotLight::SetConeShape(RadeonRays::float2 angles)
    {
        m_angles = angles;
    }
    
    inline RadeonRays::float2 SpotLight::GetConeShape() const
    {
        return m_angles;
    }
    
    inline void ImageBasedLight::SetTexture(Texture const* texture)
    {
        m_texture = texture;
    }
    
    inline Texture const* ImageBasedLight::GetTexture() const
    {
        return m_texture;
    }
    
    inline std::size_t AreaLight::GetPrimitiveIdx() const
    {
        return m_prim_idx;
    }
    
    inline Shape const* AreaLight::GetShape() const
    {
        return m_shape;
    }
}
