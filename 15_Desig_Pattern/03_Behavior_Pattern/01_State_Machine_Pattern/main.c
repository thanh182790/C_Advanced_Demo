#include <stdio.h>
#include "music-player-context.h"
#include "paused-state.h"
#include "playing-state.h"
#include "stopped-state.h"

extern void bufferingComplete(PlayerState *state);
extern void bufferingError(PlayerState *state);

int main()
{
    MusicPlayer *player = createMusicPlayer(createStoppedState());

    printf("\n[TEST] Initial the music player, current state: Stopped\n");
    player->clickStopButton(player);

    printf("\n[TEST] Press Play -> Transition to Playing\n");
    player->clickPlayButton(player);

    printf("\n[TEST] Press Pause -> Transition to Paused\n");
    player->clickPauseButton(player);

    printf("\n[TEST] Resume from Paused -> Back to Playing\n");
    player->clickPlayButton(player);

    printf("\n[TEST] Press Stop -> Back to Stopped\n");
    player->clickStopButton(player);

    destroyMusicPlayer(player);
    return 0;
}