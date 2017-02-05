#ifndef _GRAPHICS_
#define _GRAPHICS_

// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// Vulkan
#include <vulkan\vulkan.hpp>
// image Libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
#include <SOIL.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <windows.h>
#include <time.h>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <vector>
#include <array>
#include <cstring>
#include <set>
#include <chrono>
#include <unordered_map>

#include "VDeleter.h"
#include "Shader.h"
#include "../TextBox/TextBox.h"
#include "../Profile/profile.h"
#include "../utils/FileUtils.h"

#if 0
	#define _OPENGL_RENDER_
#else
	#define _VULKAN_RENDER_
#endif

namespace GameEngine {
	namespace Graphics {
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		const std::vector<const char*> validationLayers = {
			"VK_LAYER_LUNARG_standard_validation"
		};

		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
	#endif

		// Function prototypes
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

		struct QueueFamilyIndices {
			int graphicsFamily = -1;
			int presentFamily = -1;

			bool isComplete() {
				return graphicsFamily >= 0;
			}
		};

		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

		struct Vertex {
			glm::vec3 pos;
			glm::vec3 color;
			glm::vec2 texCoord;

			static VkVertexInputBindingDescription getBindingDescription() {
				VkVertexInputBindingDescription bindingDescription = {};
				bindingDescription.binding = 0;
				bindingDescription.stride = sizeof(Vertex);
				bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

				return bindingDescription;
			}

			static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
				std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

				attributeDescriptions[0].binding = 0;
				attributeDescriptions[0].location = 0;
				attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
				attributeDescriptions[0].offset = offsetof(Vertex, pos);

				attributeDescriptions[1].binding = 0;
				attributeDescriptions[1].location = 1;
				attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
				attributeDescriptions[1].offset = offsetof(Vertex, color);

				attributeDescriptions[2].binding = 0;
				attributeDescriptions[2].location = 2;
				attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
				attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

				return attributeDescriptions;
			}

			bool operator==(const Vertex& other) const {
				return pos == other.pos && color == other.color && texCoord == other.texCoord;
			}
		};

		struct UniformBufferObject {
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 proj;
		};

		class RenderWindow {
		public:
			RenderWindow(){}
			~RenderWindow(){}

			void Initialize();
			void Terminate();

			void RenderLoop();
			void RenderLoopOpenGL();
			void RenderLoopVulkan();

		private:
			// opengl
			void InitOpenGL();
			// vulkan
			void InitVulkan();
			// Vulkan initialize functions
			void initWindow();
			void createInstance();
			void setupDebugCallback();
			void createSurface();
			void pickPhysicalDevice();
			void createLogicalDevice();
			void createSwapChain();
			void createImageViews();
			void createRenderPass();
			void createDescriptorSetLayout();
			void createGraphicsPipeline();
			void createFramebuffers();
			void createCommandPool();
			void createDepthResources();
			void createTextureImage();
			void createTextureImageView();
			void createTextureSampler();
			void loadModel();
			void createVertexBuffer();
			void createIndexBuffer();
			void createUniformBuffer();
			void createDescriptorPool();
			void createDescriptorSet();
			void createCommandBuffers();
			void createSemaphores();
			// vulkan draw call
			void updateUniformBuffer();
			void drawFrame();

			// important functions
			void recreateSwapChain();
			void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VDeleter<VkImage>& image, VDeleter<VkDeviceMemory>& imageMemory);
			void createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VDeleter<VkImageView>& imageView);
			void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VDeleter<VkBuffer>& buffer, VDeleter<VkDeviceMemory>& bufferMemory);
			void copyImage(VkImage srcImage, VkImage dstImage, uint32_t width, uint32_t height);
			void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

			// Vuklan helper functions
			VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
			VkFormat findDepthFormat();
			void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
			VkCommandBuffer beginSingleTimeCommands();
			void endSingleTimeCommands(VkCommandBuffer commandBuffer);
			uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
			void createShaderModule(const std::vector<char>& code, VDeleter<VkShaderModule>& shaderModule);
			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
			VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
			SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
			bool hasStencilComponent(VkFormat format);
			bool isDeviceSuitable(VkPhysicalDevice device);
			bool checkDeviceExtensionSupport(VkPhysicalDevice device);
			QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
			std::vector<const char*> getRequiredExtensions();
			bool checkValidationLayerSupport();

			// Vulkan objects
			VDeleter<VkInstance> instance{ vkDestroyInstance };
			VDeleter<VkDebugReportCallbackEXT> callback{ instance, DestroyDebugReportCallbackEXT };
			VDeleter<VkSurfaceKHR> surface{ instance, vkDestroySurfaceKHR };

			VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
			VDeleter<VkDevice> device{ vkDestroyDevice };

			VkQueue graphicsQueue;
			VkQueue presentQueue;

			VDeleter<VkSwapchainKHR> swapChain{ device, vkDestroySwapchainKHR };
			std::vector<VkImage> swapChainImages;
			VkFormat swapChainImageFormat;
			VkExtent2D swapChainExtent;
			std::vector<VDeleter<VkImageView>> swapChainImageViews;
			std::vector<VDeleter<VkFramebuffer>> swapChainFramebuffers;

			VDeleter<VkRenderPass> renderPass{ device, vkDestroyRenderPass };
			VDeleter<VkDescriptorSetLayout> descriptorSetLayout{ device, vkDestroyDescriptorSetLayout };
			VDeleter<VkPipelineLayout> pipelineLayout{ device, vkDestroyPipelineLayout };
			VDeleter<VkPipeline> graphicsPipeline{ device, vkDestroyPipeline };

			VDeleter<VkCommandPool> commandPool{ device, vkDestroyCommandPool };

			VDeleter<VkImage> depthImage{ device, vkDestroyImage };
			VDeleter<VkDeviceMemory> depthImageMemory{ device, vkFreeMemory };
			VDeleter<VkImageView> depthImageView{ device, vkDestroyImageView };

			VDeleter<VkImage> textureImage{ device, vkDestroyImage };
			VDeleter<VkDeviceMemory> textureImageMemory{ device, vkFreeMemory };
			VDeleter<VkImageView> textureImageView{ device, vkDestroyImageView };
			VDeleter<VkSampler> textureSampler{ device, vkDestroySampler };

			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
			VDeleter<VkBuffer> vertexBuffer{ device, vkDestroyBuffer };
			VDeleter<VkDeviceMemory> vertexBufferMemory{ device, vkFreeMemory };
			VDeleter<VkBuffer> indexBuffer{ device, vkDestroyBuffer };
			VDeleter<VkDeviceMemory> indexBufferMemory{ device, vkFreeMemory };

			VDeleter<VkBuffer> uniformStagingBuffer{ device, vkDestroyBuffer };
			VDeleter<VkDeviceMemory> uniformStagingBufferMemory{ device, vkFreeMemory };
			VDeleter<VkBuffer> uniformBuffer{ device, vkDestroyBuffer };
			VDeleter<VkDeviceMemory> uniformBufferMemory{ device, vkFreeMemory };

			VDeleter<VkDescriptorPool> descriptorPool{ device, vkDestroyDescriptorPool };
			VkDescriptorSet descriptorSet;

			std::vector<VkCommandBuffer> commandBuffers;

			VDeleter<VkSemaphore> imageAvailableSemaphore{ device, vkDestroySemaphore };
			VDeleter<VkSemaphore> renderFinishedSemaphore{ device, vkDestroySemaphore };

			// window pointer and textbox
			GLFWwindow*			window;
			TextBox*			textbox;
			ParameterReader*	pd;

			// OpenGL shaders ad textures
			Shader*				ourShader;
			GLuint				VBO, VAO, EBO;
			GLuint				texture;

			// Window dimensions
			int					width;
			int					height;

			// frame rate
			int					count = 0;
			float				fps;
			long				currTime;
			long				lastTime = 0;

			// COLORS
			static COLOR colors[8];

			// Function prototypes
			static std::vector<char> readFile(const std::string& filename);
			static void onWindowResized(GLFWwindow* window, int width, int height);
			static VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
			static void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

#endif