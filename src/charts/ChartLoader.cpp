#include "ChartLoader.h"
#include "AudioSystem.h"

Chart ChartLoader::createTestChart()
{
    Chart chart;

    chart.musicPath = "C:/Users/yanni/Desktop/RhythmProject/assets/music/fassounds-escape-your-love-upbeat-fashion-pop-dance-412230.ogg";

    // Notes manuell mit unterschiedlichen Zeitpunkten und Lanes
    // Format: { Zeit (Sekunden), Lane (0-3), Dauer (0 = Normal Note) }

    chart.addNote({2.0f, 1, 2.5f});
    // Erste Sequenz: 2.0s - 3.5s
    chart.addNote({2.0f, 0, 0.0f}); // Lane 0 bei 2s
    chart.addNote({2.5f, 2, 0.0f}); // Lane 2 bei 2.5s
    chart.addNote({3.0f, 3, 0.0f}); // Lane 3 bei 3s

    // Zweite Sequenz: 4.0s - 5.0s

    // Dritte Sequenz: 6.0s - 7.0s
    chart.addNote({6.0f, 3, 0.0f});
    chart.addNote({6.4f, 2, 0.0f});
    chart.addNote({6.8f, 1, 0.0f});
    chart.addNote({7.2f, 0, 0.0f});

    // Noch ein paar weitere
    chart.addNote({8.0f, 1, 0.0f});
    chart.addNote({8.5f, 3, 0.0f});
    chart.addNote({9.0f, 0, 0.0f});

    return chart;
}
