#pragma once
#include <iostream>
#include <chrono>
#include <vector>
#include <array>
#include <numeric>
#include <algorithm>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "imgui_plot.h"

struct transform
{
    float matrix[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
};
class GameObject3D final
{
public:
    int id{};
    transform Transform{};
};
class GameObject3DAlt final
{
public:
    int id{};
    transform* Transform{};
};

class ThrashTheCache final
{
public:
    ThrashTheCache() {
        m_Results.resize(11);
        m_SavedResults.resize(3);
    };
    void Graph() {
        
        ImGui::SetNextWindowPos(ImVec2(65, 75), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(145, 240), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("excercise 2"))
        {

            ImGui::InputInt("#samples", &m_SampleAmountEx1, 1, 20);

            if (ImGui::Button("Thrash The Cache"))
            {
                
                m_Measurments.clear();
                m_Measurments.resize(m_SampleAmountEx1 +1);
                CalcResultint();
                CalcResult();
                m_SavedResults[0] = m_Results;
            };
            static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
            ImGui::PlotConfig conf;
           ;
           if (!m_SavedResults[0].empty())
           {
               conf.values.xs = stepsizes; 
               conf.values.ys = m_SavedResults[0]._Unchecked_begin();
               conf.values.count = 11;
               conf.scale.min = -1;

               conf.scale.max = *std::max_element(m_SavedResults[0].begin(), m_SavedResults[0].end());
               conf.tooltip.show = true;
               conf.tooltip.format = "x=%.2f, y=%.2f";
               conf.grid_y.show = true;
               conf.grid_y.size = static_cast<float>(*std::max_element(m_SavedResults[0].begin(), m_SavedResults[0].end()) / 10);
               conf.frame_size = ImVec2(200, 100);
               conf.line_thickness = 2.f;
               conf.values.color = ImColor(255, 171, 74);

               ImGui::Plot("plot", conf);
            }
        }
        ImGui::End();

        if (ImGui::Begin("excercise 3"))
        {

            ImGui::InputInt("#samples", &m_SampleAmountEx2, 1, 20);

            if (ImGui::Button("Thrash The Cache with GameObject3D"))
            {

                m_Measurments.clear();
                m_Measurments.resize(m_SampleAmountEx2 + 1);
                CalcResult3D();
                CalcResult();
                m_SavedResults[1] = m_Results;

            };
            
            

            if (!m_SavedResults[1].empty())
            {
                ImGui::PlotConfig conf;
                conf.values.xs = stepsizes;
                conf.values.ys = m_SavedResults[1]._Unchecked_begin();
                conf.values.count = 11;
                conf.scale.min = -1;

                conf.scale.max = *std::max_element(m_SavedResults[1].begin(), m_SavedResults[1].end());
                conf.tooltip.show = true;
                conf.tooltip.format = "x=%.2f, y=%.2f";
                conf.grid_y.show = true;
                conf.grid_y.size = static_cast<float>(*std::max_element(m_SavedResults[1].begin(), m_SavedResults[1].end()) / 10);
                
                conf.frame_size = ImVec2(200, 100);
                conf.line_thickness = 2.f;
                conf.values.color = ImColor(98, 255, 84);

                ImGui::Plot("plot1", conf);
            }

            

            if (ImGui::Button("Thrash The Cache with GameObject3DAlt"))
            {

                m_Measurments.clear();
                m_Measurments.resize(m_SampleAmountEx2 + 1);
                CalcResult3DAlt();
                CalcResult();
                m_SavedResults[2] = m_Results;

            };

            if (!m_SavedResults[2].empty())
            {
                ImGui::PlotConfig conf;
                conf.values.xs = stepsizes;
                conf.values.ys = m_SavedResults[2]._Unchecked_begin();
                conf.values.count = 11;
                conf.scale.min = -1;

                conf.scale.max = *std::max_element(m_SavedResults[2].begin(), m_SavedResults[2].end());
                conf.tooltip.show = true;
                conf.tooltip.format = "x=%.2f, y=%.2f";
                conf.grid_y.show = true;
                conf.grid_y.size = static_cast<float>(*std::max_element(m_SavedResults[2].begin(), m_SavedResults[2].end()) / 10);
                
                conf.frame_size = ImVec2(200, 100);
                conf.line_thickness = 2.f;
                conf.values.color = ImColor(66, 214, 255);

                ImGui::Plot("plot2", conf);
            }

            if (!m_SavedResults[1].empty() and !m_SavedResults[2].empty())
            {
                static const float* y_data[] = { m_SavedResults[1]._Unchecked_begin(), m_SavedResults[2]._Unchecked_begin() };
                static ImU32 colors[2] = { ImColor(98,255,84), ImColor(66, 214, 255)};
                static uint32_t selection_start = 0, selection_length = 0;


                // Draw first plot with multiple sources
                ImGui::PlotConfig conf;
                conf.values.xs = stepsizes;
                conf.values.count = 11;
                conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
                conf.values.ys_count = 2;
                conf.values.colors = colors;
                conf.scale.min = -1;
                conf.scale.max = *std::max_element(m_SavedResults[1].begin(), m_SavedResults[1].end());
                conf.tooltip.show = true;
                conf.tooltip.format = "x=%.2f, y=%.2f";
                conf.grid_y.show = true;
                conf.grid_y.size = static_cast<float>(*std::max_element(m_SavedResults[1].begin(), m_SavedResults[1].end()) / 10);;
                
                
                conf.selection.show = true;
                conf.selection.start = &selection_start;
                conf.selection.length = &selection_length;
                conf.line_thickness = 2.f;
                conf.frame_size = ImVec2(200, 100);
                ImGui::Plot("plot3", conf);
            }

        }
        ImGui::End();
        
    };
    
private:
    void CalcResult3D() {
        m_CurrentLoop = 0;
        GameObject3D* Go3DArr = new GameObject3D[m_LargeNumber]{};
        for (int index{}; index < m_SampleAmountEx2; ++index)
        {
            for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < m_LargeNumber - 1; i += stepsize)
                {
                    Go3DArr[i].id *= 2;
                }
                auto end = std::chrono::high_resolution_clock::now();

                auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                m_Measurments[m_CurrentLoop].emplace_back(static_cast<float>(elapsedTime));
                //std::cout << stepsize << "; " << elapsedTime << std::endl;
            }
            ++m_CurrentLoop;

        }
        delete[] Go3DArr;
    };
    void CalcResultint() {
        m_CurrentLoop = 0;
        int* intArr = new int[m_LargeNumber] {};
        for (int index{}; index < m_SampleAmountEx1; ++index)
        {
            for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < m_LargeNumber - 1; i += stepsize)
                {
                    intArr[i] *= 2;
                }
                auto end = std::chrono::high_resolution_clock::now();

                auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                m_Measurments[m_CurrentLoop].emplace_back(static_cast<float>(elapsedTime));
                //std::cout << stepsize << "; " << elapsedTime << std::endl;
            }
            ++m_CurrentLoop;
            
        }
        delete[] intArr;
    };
    void CalcResult3DAlt() {
        m_CurrentLoop = 0;
        GameObject3DAlt* Go3DAltArr = new GameObject3DAlt[m_LargeNumber] {};
        for (int index{}; index < m_SampleAmountEx2; ++index)
        {
            for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < m_LargeNumber - 1; i += stepsize)
                {
                    Go3DAltArr[i].id *= 2;
                }
                auto end = std::chrono::high_resolution_clock::now();

                auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                m_Measurments[m_CurrentLoop].emplace_back(static_cast<float>(elapsedTime));
                //std::cout << stepsize << "; " << elapsedTime << std::endl;
            }
            ++m_CurrentLoop;
            
        }
        delete[] Go3DAltArr;
    };
    void CalcResult() {
        m_Results.clear();
        m_Results.resize(11);
        for (int index{}; index < 11; ++index)
        {
            std::vector<float>temp(10);
            for (int index2{}; index2 < 10; ++index2)
            {
                temp[index2] = m_Measurments[index2][index];
            }
            temp.erase(std::ranges::max_element(temp));
            temp.erase(std::ranges::min_element(temp));
            m_Results[index] = std::accumulate(temp.begin(), temp.end(), static_cast<float>(0)) / temp.size();
            std::cout << m_Results[index] << std::endl;
        }
        
    };

    
    int m_AmountMeasurements{ 10 };
    int m_LargeNumber{ 9000000 };
    int m_SampleAmountEx1{ 10 };
    int m_SampleAmountEx2{ 100 };
    int m_CurrentLoop{};

    float stepsizes[11]{1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f, 512.f, 1024.f};

    std::vector<std::vector<float>> m_Measurments{};
    std::vector<float> m_Results{};
    std::vector<std::vector<float>> m_SavedResults{};
    
};



// TrashTheCashConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//




