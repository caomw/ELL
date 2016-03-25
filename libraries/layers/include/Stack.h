////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Rockmill
//  File:     Stack.h (layers)
//  Authors:  Ofer Dekel, Chuck Jacobs
//
//  [copyright]
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Layer.h"
#include "Coordinate.h"

// stl
#include <string>
#include <iostream>
#include <vector>
#include <memory>

namespace layers
{
    /// <summary> Implements a stack of layers. </summary>
    class Stack
    {
    public:
        /// <summary> Constructs an instance of Stack with a single input layer. </summary>
        Stack();

        /// <summary> Deleted copy constructor </summary>
        Stack(const Stack&) = delete;

        /// <summary> Default move constructor </summary>
        Stack(Stack&&) = default;

        /// <summary> Virtual destructor. </summary>
        virtual ~Stack() = default;

        /// <summary> Adds a layer to the stack. </summary>
        ///
        /// <param name="layer"> The layer to add to the stack. </param>
        ///
        /// <returns> The index of the added layer. </returns>
        uint64_t AddLayer(std::unique_ptr<Layer>&& layer);

        /// <summary> Returns the number of layers in the stack. </summary>
        ///
        /// <returns> The total number of layers in the stack. </returns>
        uint64_t NumLayers() const;

        /// <summary> Gets a Layer cast as a specified layer type, used when derived classes add functionality to layers </summary>
        ///
        /// <typeparam name="LayerType"> Layer type to return. </typeparam>
        /// <param name="layerIndex"> Zero-based index of the layer. </param>
        ///
        /// <returns> The requested layer, cast to a const reference of the requested type. </returns>
        template <typename LayerType = Layer>
        const LayerType& GetLayer(uint64_t layerIndex) const;

        /// <summary> Gets the list of coordinates in a given layer. </summary>
        ///
        /// <param name="layerIndex"> Zero-based index of the layer. </param>
        ///
        /// <returns> The coordinate list. </returns>
        CoordinateList GetCoordinateList(uint64_t layerIndex) const;

        /// <summary> Static function that loads a Stack from file. </summary>
        ///
        /// <typeparam name="StackType"> Stack type to load. </typeparam>
        /// <param name="inputStackFile"> Name of the stack file to load. </param>
        ///
        /// <returns> A StackType. </returns>
        template<typename StackType = Stack>
        static StackType Load(const std::string& inputStackFile);

        /// <summary> Saves a stack to an output stream. </summary>
        ///
        /// <param name="os"> [in,out] Stream to write data to. </param>
        void Save(std::ostream& os) const;

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName();

        /// <summary> Reads the stack from an XMLDeserializer. </summary>
        ///
        /// <param name="deserializer"> [in,out] The deserializer. </param>
        void Read(utilities::XMLDeserializer& deserializer);

        /// <summary> Writes the stack to an XMLSerializer. </summary>
        ///
        /// <param name="serializer"> [in,out] The serializer. </param>
        void Write(utilities::XMLSerializer& serializer) const;

    protected:
        // members
        std::vector<std::unique_ptr<Layer>> _layers;

        void IncreaseInputLayerSize(uint64_t minSize);

    private:
        static const int _currentVersion = 1;
    };
}

#include "../tcc/Stack.tcc"