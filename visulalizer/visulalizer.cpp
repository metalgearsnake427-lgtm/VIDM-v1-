#include "player.h"
#include "controls.h"
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>

int init_player(PlayerState *is, const char *filename) {
    if (!is || !filename) return -1; // Check for null pointers
    is->pFormatCtx = NULL;

    if (avformat_open_input(&(is->pFormatCtx), filename, NULL, NULL) != 0) {
        return -1; // Error opening file
    }

    if (avformat_find_stream_info(is->pFormatCtx, NULL) < 0) {
        avformat_close_input(&(is->pFormatCtx));
        return -1; // Error finding stream info
    }

    is->videoStream = -1;
    for (int i = 0; i < is->pFormatCtx->nb_streams; i++) {
        if (is->pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            is->videoStream = i;
            break;
        }
    }

    if (is->videoStream == -1) {
        avformat_close_input(&(is->pFormatCtx));
        return -1; // No video stream found
    }

    if (stream_component_open(is) < 0) {
        avformat_close_input(&(is->pFormatCtx));
        return -1; // Error opening stream component
    }

    return 0;
}

int stream_component_open(PlayerState *is) {
    if (!is || is->videoStream < 0) return -1; // Check for valid state

    AVCodecParameters *pCodecPar = is->pFormatCtx->streams[is->videoStream]->codecpar;
    AVCodec *pCodec = avcodec_find_decoder(pCodecPar->codec_id);
    if (!pCodec) return -1; // Codec not found

    is->pCodecCtx = avcodec_alloc_context3(pCodec);
    if (!is->pCodecCtx) return -1; // Allocation failed

    if (avcodec_parameters_to_context(is->pCodecCtx, pCodecPar) < 0) {
        avcodec_free_context(&(is->pCodecCtx));
        return -1; // Parameter setting failed
    }

    if (avcodec_open2(is->pCodecCtx, pCodec, NULL) < 0) {
        avcodec_free_context(&(is->pCodecCtx));
        return -1; // Codec opening failed
    }

    is->window = SDL_CreateWindow("Advanced Modular Player", 
                                  SDL_WINDOWPOS_UNDEFINED, 
                                  SDL_WINDOWPOS_UNDEFINED, 
                                  is->pCodecCtx->width, 
                                  is->pCodecCtx->height, 
                                  0);
    
    if (!is->window) {
        avcodec_free_context(&(is->pCodecCtx));
        return -1; // Window creation failed
    }

    is->renderer = SDL_CreateRenderer(is->window, -1, 0);
    if (!is->renderer) {
        SDL_DestroyWindow(is->window);
        avcodec_free_context(&(is->pCodecCtx));
        return -1; // Renderer creation failed
    }

    is->texture = SDL_CreateTexture(is->renderer, 
                                    SDL_PIXELFORMAT_YV12, 
                                    SDL_TEXTUREACCESS_STREAMING, 
                                    is->pCodecCtx->width, 
                                    is->pCodecCtx->height);
    if (!is->texture) {
        SDL_DestroyRenderer(is->renderer);
        SDL_DestroyWindow(is->window);
        avcodec_free_context(&(is->pCodecCtx));
        return -1; // Texture creation failed
    }

    is->paused = false;
    is->quit = false;

    return 0; // Success
}

void video_display(PlayerState *is) {
    if (!is || !is->renderer) return; // Check for valid state
    SDL_RenderPresent(is->renderer);
}

// Cleanup function to free resources
void cleanup_player(PlayerState *is) {
    if (is) {
        if (is->texture) SDL_DestroyTexture(is->texture);
        if (is->renderer) SDL_DestroyRenderer(is->renderer);
        if (is->window) SDL_DestroyWindow(is->window);
        if (is->pCodecCtx) avcodec_free_context(&(is->pCodecCtx));
        if (is->pFormatCtx) avformat_close_input(&(is->pFormatCtx));
    }
}
