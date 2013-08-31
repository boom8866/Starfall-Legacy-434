DELETE FROM `access_requirement` WHERE  `mapId`=269 AND `difficulty`=0;
DELETE FROM `access_requirement` WHERE  `mapId`=269 AND `difficulty`=1;
INSERT INTO `access_requirement` (`mapId`, `difficulty`, `level_min`, `level_max`, `item`, `item2`, `quest_done_A`, `quest_done_H`, `completed_achievement`, `quest_failed_text`, `comment`) VALUES 
(269, 0, 66, 0, 0, 0, 0, 0, 0, '', 'Caverns Of Time,Black Morass (Entrance)'),
(269, 1, 70, 0, 0, 0, 0, 0, 0, '', 'Caverns Of Time,Black Morass (Entrance)');