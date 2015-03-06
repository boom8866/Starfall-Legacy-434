UPDATE `creature` SET `phaseMask`=132096 WHERE `guid` IN (841884, 841885, 841886, 841887);
UPDATE `phase_definitions` SET `phasemask`=131072, `comment`='Twilight Highlands [A]: Add Phase 131072 On Quest Accepted: Nightmare [27380]' WHERE `zoneId`=4922 AND `entry`=31;
UPDATE `phase_definitions` SET `phasemask`=131072, `comment`='Twilight Highlands [A]: Add Phase 131072 On Quest Complete: Nightmare [27380]' WHERE `zoneId`=4922 AND `entry`=32;

