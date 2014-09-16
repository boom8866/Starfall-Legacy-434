DELETE FROM `game_event_gameobject` WHERE `guid` IN (716532, 716551);
INSERT INTO `game_event_gameobject` (`eventEntry`, `guid`) VALUES
(1, 716532),
(1, 716551);

DELETE FROM `game_event_creature` WHERE `guid` IN (728672, 728670);
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
(1, 728672),
(1, 728670);