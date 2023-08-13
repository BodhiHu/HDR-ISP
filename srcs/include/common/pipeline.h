/**
 * @file pipeline.h
 * @author joker.mao (joker_mao@163.com)
 * @brief
 * @version 0.1
 * @date 2023-07-27
 *
 * Copyright (c) of ADAS_EYES 2023
 *
 */

#ifndef ISP_PIPE_H
#define ISP_PIPE_H

#include <list>
#include <functional>

#include "modules/modules.h"
#include <chrono>

class IspPipeline
{
private:
    /* data */
    std::list<IspModule> pipe_;
    bool is_pipe_vaild_ = false;

public:
    IspPipeline()
    {
        pipe_.clear();
    }
    ~IspPipeline()
    {
        pipe_.clear();
    }

    IspPipeline(std::list<std::string> pipeline)
    {
        MakePipe(pipeline);
    }

    int MakePipe(const std::list<std::string> &pipeline_str)
    {
        IspModule mod;
        IspModule last_mod;
        for (auto item : pipeline_str)
        {
            if (0 == GetIspModuleFromName(item, mod))
            {
                if (pipe_.size() > 0)
                {
                    if ((mod.in_type != last_mod.out_type) || (mod.in_domain != last_mod.out_domain))
                    {
                        if ((mod.in_domain != last_mod.out_domain))
                            LOG(ERROR) << "mod " << mod.name << " domain is not equal wait " << last_mod.name;
                        if (mod.in_type != last_mod.out_type)
                            LOG(ERROR) << "mod " << mod.name << " in bit is not equal wait " << last_mod.name;
                        is_pipe_vaild_ = false;
                        return -1;
                    }
                }
                pipe_.push_back(mod);
                last_mod = mod;
            }
            else
            {
                LOG(WARNING) << item << " find failed";
            }
        }
        is_pipe_vaild_ = true;
        return 0;
    }

    int RunPipe(Frame *frame, const IspPrms *prms)
    {
        if (!is_pipe_vaild_)
        {
            LOG(ERROR) << "pipeline is not vailed..";
            return -1;
        }
        // uint64_t start_tick, end_tick;
        LOG(INFO) << "============= user pipeline running ==============";
        for (auto isp_mod : pipe_)
        {
            auto start_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            if (isp_mod.run_function(frame, prms) != 0)
            {
                LOG(ERROR) << "pipeline run failed, mod " << isp_mod.name;
                return -1;
            }
            auto end_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            LOG(INFO) << "mod " << isp_mod.name << "\t time: " << (end_ms - start_ms).count() << "ms";
        }
        LOG(INFO) << "============= user pipeline running end ==============";
        return 0;
    }

    int PrintPipe()
    {
        if (!is_pipe_vaild_)
        {
            LOG(ERROR) << "pipeline is not vailed..";
            return -1;
        }
        int index = 0;
        LOG(INFO) << "============= user pipeline print start ==============";
        for (auto isp_mod : pipe_)
        {
            LOG(INFO) << "mod[" << index++ << "] -> " << isp_mod.name;
        }
        LOG(INFO) << "============= user pipeline print end ==============";
        return 0;
    }
};

void IspInit();

#endif // ! ISP_PIPE_H