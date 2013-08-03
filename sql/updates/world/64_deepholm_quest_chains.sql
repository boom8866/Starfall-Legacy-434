
/*
Von    : Hanfblatt
Beschr : First 2 Fragments Quest Chains
Ticket :
*/

-- Temple of Earth Twilight Portals and Portal to Therazone's Throne
UPDATE `gameobject` SET `phaseMask` = 32768 WHERE `id` = 205081 AND `map` = 646;
UPDATE `gameobject` SET `phaseMask` = 32768 WHERE `guid` = 718368;
UPDATE `gameobject_template` SET `flags` = 16 WHERE  `entry`=205081;

-- Middle World Pillar Fragment
UPDATE `quest_template` SET `PrevQuestId`= 26409, `NextQuestId`= 26411, `ExclusiveGroup`= -26410 WHERE  `Id`=26410;
UPDATE `quest_template` SET `PrevQuestId`= 26409, `NextQuestId`= 26411, `ExclusiveGroup`= -26410 WHERE  `Id`=27135;
UPDATE `quest_template` SET `PrevQuestId`= 27931, `NextQuestId`= 27934, `ExclusiveGroup`= -27933 WHERE  `Id`=27933;
UPDATE `quest_template` SET `PrevQuestId`= 27931, `NextQuestId`= 27934, `ExclusiveGroup`= -27933 WHERE  `Id`=27932;
UPDATE `quest_template` SET `PrevQuestId`= 0 WHERE  `Id`= 26625;
UPDATE `quest_template` SET `NextQuestId`= 26625, `ExclusiveGroup`= -26537 WHERE  `Id`= 26564;
UPDATE `quest_template` SET `NextQuestId`= 26625, `ExclusiveGroup`= -26537 WHERE  `Id`= 26591;
UPDATE `quest_template` SET `NextQuestId`= 26625, `ExclusiveGroup`= -26537 WHERE  `Id`= 26537;
UPDATE `quest_template` SET `NextQuestId`= 26591, `ExclusiveGroup`= -26501 WHERE  `Id`= 26502;
UPDATE `quest_template` SET `NextQuestId`= 26591, `ExclusiveGroup`= -26501 WHERE  `Id`= 26501;
UPDATE `quest_template` SET `PrevQuestId`= 27935 WHERE  `Id`= 26499;
UPDATE `quest_template` SET `PrevQuestId`= 27935 WHERE  `Id`= 26500;
UPDATE `quest_template` SET `PrevQuestId`= 26755, `NextQuestId`= 26834, `ExclusiveGroup`= -26762 WHERE  `Id`= 26770;
UPDATE `quest_template` SET `PrevQuestId`= 26755, `NextQuestId`= 26834, `ExclusiveGroup`= -26762 WHERE  `Id`= 26762;
UPDATE `quest_template` SET `PrevQuestId`= 0 WHERE  `Id`= 26834;
UPDATE `quest_template` SET `PrevQuestId`= 26834, `NextQuestId`= 26835, `ExclusiveGroup`= -26791 WHERE  `Id`= 26791;
UPDATE `quest_template` SET `PrevQuestId`= 26834, `NextQuestId`= 26835, `ExclusiveGroup`= -26791 WHERE  `Id`= 26792;
UPDATE `quest_template` SET `PrevQuestId`=26625 WHERE  `Id`=27126;

-- Upper World Pillar Fragment
UPDATE `quest_template` SET `NextQuestId`= 26247, `ExclusiveGroup`= -26244 WHERE  `Id`= 26245;
UPDATE `quest_template` SET `NextQuestId`= 26247, `ExclusiveGroup`= -26244 WHERE  `Id`= 26244;
UPDATE `quest_template` SET `NextQuestId`= 26247, `ExclusiveGroup`= -26244 WHERE  `Id`= 26246;
UPDATE `quest_template` SET `PrevQuestId`= 26248 WHERE  `Id`= 26250;
UPDATE `quest_template` SET `PrevQuestId`= 27061 WHERE  `Id`= 28866;
UPDATE `quest_template` SET `PrevQuestId`= 27061, `NextQuestId`= 26771, `ExclusiveGroup`= -26766 WHERE  `Id`= 26768;
UPDATE `quest_template` SET `PrevQuestId`= 27061, `NextQuestId`= 26771, `ExclusiveGroup`= -26766 WHERE  `Id`= 26766;
UPDATE `quest_template` SET `PrevQuestId`= 26771, `NextQuestId`= 26876, `ExclusiveGroup`= -26857 WHERE  `Id`= 26861;
UPDATE `quest_template` SET `PrevQuestId`= 26771, `NextQuestId`= 26876, `ExclusiveGroup`= -26857 WHERE  `Id`= 26857;
UPDATE `quest_template` SET `PrevQuestId`= 0 WHERE  `Id`= 26876;
UPDATE `quest_template` SET `NextQuestId`= 26326, `ExclusiveGroup`= -26876 WHERE  `Id`= 26876;
UPDATE `quest_template` SET `NextQuestId`= 26326, `ExclusiveGroup`= -26876 WHERE  `Id`= 27938;
UPDATE `quest_template` SET `PrevQuestId`= 26255 WHERE  `Id`= 26259;
UPDATE `quest_template` SET `PrevQuestId`= 26247 WHERE  `Id`= 26249;
UPDATE `quest_template` SET `PrevQuestId`= 26247 WHERE  `Id`= 26248;

-- The Very Near Erath Beneath Our Feet
UPDATE `quest_template` SET `PrevQuestId`= 26326, `NextQuestId`= 26315, `ExclusiveGroup`= -26312 WHERE  `Id`= 26312;
UPDATE `quest_template` SET `PrevQuestId`= 26326, `NextQuestId`= 26315, `ExclusiveGroup`= -26312 WHERE  `Id`= 26313;
UPDATE `quest_template` SET `PrevQuestId`= 26326, `NextQuestId`= 26315, `ExclusiveGroup`= -26312 WHERE  `Id`= 26314;
UPDATE `quest_template` SET `PrevQuestId`= 26315 WHERE  `Id`= 26328;
DELETE FROM `creature_involvedrelation` WHERE `id` = 42467 AND `quest` IN (26328, 26871);
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
(42467, 26328),
(42467, 26871);
DELETE FROM `creature_questrelation` WHERE `id` = 42467 AND `quest` IN (26377, 26376, 26426, 26436);
DELETE FROM `creature_questrelation` WHERE `id` = 42899 AND `quest` = 26375;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES 
(42467, 26377),
(42467, 26376),
(42467, 26426),
(42467, 26436),
(42899, 26375);
DELETE FROM `creature_involvedrelation` WHERE `id` = 42467 AND `quest` IN (26377, 26376);
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
(42467, 26377),
(42467, 26376);
UPDATE `quest_template` SET `RequiredRaces`=0 WHERE  `Id`=28869;
UPDATE `quest_template` SET `RequiredRaces`=0 WHERE  `Id`=26436;
UPDATE `quest_template` SET `RequiredRaces`=0 WHERE  `Id`=26437;
UPDATE `quest_template` SET `RequiredRaces`=0 WHERE  `Id`=26438;
DELETE FROM `creature_involvedrelation` WHERE `id` = 42899 AND `quest` = 26375;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES (42899, 26375);
UPDATE `quest_template` SET `Flags`=8519816 WHERE  `Id`=26426;
UPDATE `creature` SET `npcflag`=2 WHERE  `guid`=741139;
UPDATE `creature_template` SET `npcflag`=2 WHERE  `entry`=42899;
UPDATE `gameobject_template` SET `flags`=32 WHERE  `entry`=204959;
UPDATE `quest_template` SET `PrevQuestId`= 26328, `NextQuestId`= 26426, `ExclusiveGroup`= -26375 WHERE  `Id`= 26377;
UPDATE `quest_template` SET `PrevQuestId`= 26328, `NextQuestId`= 26426, `ExclusiveGroup`= -26375 WHERE  `Id`= 26376;
UPDATE `quest_template` SET `PrevQuestId`= 26328, `NextQuestId`= 26426, `ExclusiveGroup`= -26375 WHERE  `Id`= 26375;
UPDATE `quest_template` SET `PrevQuestId`= 26426 WHERE  `Id`= 26869;
UPDATE `quest_template` SET `PrevQuestId`= 26869 WHERE  `Id`= 26871;
UPDATE `quest_template` SET `PrevQuestId`= 26871 WHERE  `Id`= 28824;
UPDATE `quest_template` SET `PrevQuestId`= 26871 WHERE  `Id`= 26436;
UPDATE `quest_template` SET `PrevQuestId`= 26436 WHERE  `Id`= 26438;
UPDATE `quest_template` SET `PrevQuestId`= 26436 WHERE  `Id`= 26437;
UPDATE `quest_template` SET `PrevQuestId`= 26436 WHERE  `Id`= 26439;
UPDATE `quest_template` SET `PrevQuestId`= 26439 WHERE  `Id`= 28869;
UPDATE `quest_template` SET `PrevQuestId`= 26439 WHERE  `Id`= 26440;
UPDATE `quest_template` SET `PrevQuestId`= 26440 WHERE  `Id`= 26441;
UPDATE `quest_template` SET `RequiredRaces`=0 WHERE  `Id`=26441;
UPDATE `quest_template` SET `RequiredRaces`=0, `PrevQuestId`=26441, `NextQuestId`= 26576, `ExclusiveGroup`= -26507 WHERE  `Id`=26507;
UPDATE `quest_template` SET `RequiredRaces`=0, `PrevQuestId`=26441, `NextQuestId`= 26576, `ExclusiveGroup`= -26507 WHERE  `Id`=26575;
UPDATE `quest_template` SET `PrevQuestId`= 26575 WHERE  `Id`= 26577;
UPDATE `quest_template` SET `RequiredRaces`=0 WHERE  `Id`=26576;
UPDATE `quest_template` SET `RequiredRaces`=0 WHERE  `Id`=26577;
UPDATE `quest_template` SET `Flags`=8519816 WHERE  `Id`=26577;
UPDATE `quest_template` SET `PrevQuestId`=26656, `NextQuestId`= 26659, `ExclusiveGroup`= -26657 WHERE  `Id`=26657;
UPDATE `quest_template` SET `PrevQuestId`=26656, `NextQuestId`= 26659, `ExclusiveGroup`= -26657 WHERE  `Id`=26658;
UPDATE `quest_template` SET `PrevQuestId`=0, `NextQuestId`= 26750, `ExclusiveGroup`= -26584 WHERE  `Id`=26659;
UPDATE `quest_template` SET `PrevQuestId`=26582, `NextQuestId`= 26750, `ExclusiveGroup`= -26584 WHERE  `Id`=26584;
UPDATE `quest_template` SET `PrevQuestId`=26582, `NextQuestId`= 26750, `ExclusiveGroup`= -26584 WHERE  `Id`=26585;
UPDATE `quest_template` SET `PrevQuestId`= 26577 WHERE  `Id`= 26580;
UPDATE `quest_template` SET `PrevQuestId`= 26577 WHERE  `Id`= 26578;
UPDATE `quest_template` SET `PrevQuestId`= 26577 WHERE  `Id`= 26579;
UPDATE `quest_template` SET `PrevQuestId`= 26580 WHERE  `Id`= 26581;
UPDATE `quest_template` SET `PrevQuestId`= 26581 WHERE  `Id`= 26582;
UPDATE `quest_template` SET `PrevQuestId`= 26582 WHERE  `Id`= 26583;
UPDATE `quest_template` SET `PrevQuestId`=26828, `NextQuestId`= 26833, `ExclusiveGroup`= -26829 WHERE  `Id`=26829;
UPDATE `quest_template` SET `PrevQuestId`=26828, `NextQuestId`= 26833, `ExclusiveGroup`= -26829 WHERE  `Id`=26832;
UPDATE `quest_template` SET `PrevQuestId`=26828, `NextQuestId`= 26833, `ExclusiveGroup`= -26829 WHERE  `Id`=26831;
UPDATE `quest_template` SET `PrevQuestId`= 26833 WHERE  `Id`= 26875;
UPDATE `quest_template` SET `PrevQuestId`= 26875 WHERE  `Id`= 26971;
UPDATE `quest_template` SET `Flags`=262280 WHERE  `Id`=26875;
UPDATE `quest_template` SET `Flags`=4232 WHERE  `Id`=28391
