#pragma once
#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include "precompiled.h"
#include <map>
#include <type_traits>
#include <stdexcept>
#include "Shape.h"


namespace IntersectionChecker {

	class ShapeFactory {
	public:
		ShapeFactory() = default;
		~ShapeFactory() = default;

		ShapeFactory(const ShapeFactory&) = delete;
		ShapeFactory& operator=(const ShapeFactory&) = delete;


	private:
		/// <summary>
		/// Create some helper classes for the factory
		/// </summary>
		

		/// <summary>
		/// Base class creator for the shapes
		/// </summary>
		class Creator {
		public:
			Creator() = default;
			virtual ~Creator() = default;

			/// <summary>
			/// Method for creating the object, relay on overriding method
			/// </summary>
			/// <returns></returns>
			std::unique_ptr<Shape> Create() { return std::move(CreateShape()); }

		protected:
			/// <summary>
			/// each shape will override this method for specific creation of the object
			/// </summary>
			/// <returns></returns>
			virtual std::unique_ptr<Shape> CreateShape() = 0;
		};


		/// <summary>
		/// Create all shapes creators which inherits the Creator class through templates
		/// </summary>
		template <class T>
		class ShapeCreator : public Creator {
		public:
			ShapeCreator() = default;
			virtual ~ShapeCreator() = default;
		protected:
			virtual std::unique_ptr<Shape> CreateShape() override { return std::make_unique<T>(); }
		};



	private:
		/// <summary>
		/// list of factories to make all the classes registered
		/// </summary>
		std::map<std::string, std::shared_ptr<Creator>> factories;

	public:
		/// <summary>
		/// Register a class to the factory given the name as an id
		/// </summary>
		template <class T>
		void Register(const std::string& name) {
			//only admit classes inherited from shape class
			static_assert(!std::is_base_of<T, Shape>::value, 
				"ShapeFactory::Register => type not derived from base class Shape.");
	

			if (factories.find(name) != factories.end()) {
				throw std::runtime_error("ShapeFactory::Register => Id/name already exists.");
			}

			//store the creator of the specific class
			factories[name] = std::make_unique<ShapeCreator<T>>();
		}

		/// <summary>
		/// Create an object of the given name, using a stored creator
		/// If no registered before (thus, no creator available) it will return nullptr
		/// </summary>
		/// <param name="type">name of the object to create</param>
		/// <returns>Object created or nullptr if not registered</returns>
		std::shared_ptr<Shape> Create(const std::string& type) const {
			if (factories.find(type) != factories.end()) {
				auto& objcreator = factories.at(type);
				return objcreator->Create();
			}

			return nullptr;
		}
	};

}

#endif // !SHAPE_FACTORY_H