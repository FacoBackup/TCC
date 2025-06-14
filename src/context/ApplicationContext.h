#ifndef TCC_IESB_APPLICATIONCONTEXT_H
#define TCC_IESB_APPLICATIONCONTEXT_H
#define CACHED_PATH "/metal-engine-cached.txt"
#include <string>

#include "engine/EngineContext.h"
#include "glfw/GLFWContext.h"
#include "vulkan/VulkanContext.h"
#include "../repository/framebuffer/CoreFrameBuffers.h"
#include "../repository/buffers/CoreBuffers.h"
#include "../repository/descriptors/CoreDescriptorSets.h"

#include "../service/framebuffer/FrameBufferService.h"
#include "../service/pipeline/PipelineService.h"
#include "../service/buffer/BufferService.h"
#include "../service/descriptor/DescriptorService.h"
#include "../service/theme/ThemeService.h"
#include "../service/camera/CameraService.h"
#include "../service/controls/ControlService.h"
#include "./engine/passes/PassesService.h"

#include "../repository/runtime/RuntimeRepository.h"
#include "../repository/editor/GlobalRepository.h"
#include "../repository/editor/SpectrogramRepository.h"
#include "../repository/notification/NotificationRepository.h"
#include "editor/EditorPanel.h"
#include "../service/audio/AudioProcessorService.h"
#include "../service/voxel/VoxelProcessorService.h"
#include "gui/GuiContext.h"

namespace Metal {
    class ApplicationContext {
        bool debugMode;
        EditorPanel editorPanel;
        std::string rootDirectory;

    public:
        EngineContext engineContext{*this};
        PassesService passesService{*this};
        VulkanContext vulkanContext{*this, debugMode};
        GuiContext guiContext{*this};
        GLFWContext glfwContext{*this};

        // // ----------- CORE REPOSITORIES
        CoreFrameBuffers coreFrameBuffers{*this};
        CoreBuffers coreBuffers{*this};
        CoreDescriptorSets coreDescriptorSets{*this};
        // ----------- CORE REPOSITORIES

        // ----------- Services
        FrameBufferService framebufferService{*this};
        PipelineService pipelineService{*this};
        BufferService bufferService{*this};
        DescriptorService descriptorService{*this};
        ThemeService themeService{*this};
        CameraService cameraService{*this};
        AudioProcessorService audioProcessorService{*this};
        VoxelProcessorService voxelProcessorService{*this};
        ControlService controlService{*this};
        // ----------- Services

        // ----------- Repository
        RuntimeRepository runtimeRepository{};
        SpectrogramRepository spectrogramRepository;
        GlobalRepository globalRepository;
        NotificationRepository notificationRepository{};
        // ----------- Repository

        [[nodiscard]] bool isDebugMode() const { return debugMode; }

        [[nodiscard]] bool isValidContext() const {
            return glfwContext.isValidContext();
        }

        [[nodiscard]] const std::string &getRootDirectory() const {
            return rootDirectory;
        }

        [[nodiscard]] std::string getAssetRefDirectory() const {
            return rootDirectory + "/assets-ref/";
        }

        [[nodiscard]] std::string getShadersDirectory() const {
            return std::filesystem::current_path().string() + "/shaders/";
        }

        [[nodiscard]] std::string getAssetDirectory() const {
            return rootDirectory + "/assets/";
        }

        [[nodiscard]] uint32_t getFrameIndex() const;

        void start();

        explicit ApplicationContext(const bool debugMode): debugMode(debugMode) {
            editorPanel.setContext(this);
        }
    };
}

#endif
