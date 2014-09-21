DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4714' AND `SourceEntry` NOT IN (1);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4714, 2, 0, 0, 8, 0, 14375, 0, 0, 0, 0, 0, '', 'Gilneas - Add Phase 2048 after quest 14375 - Chapter 2 Default Phase 2048'),
(25, 4714, 6, 0, 0, 8, 0, 14375, 0, 0, 0, 0, 0, '', 'Gilneas - Add Phase 2 after quest 14375 - Chapter 2 Questgiver Phase 2'),
(25, 4714, 3, 0, 0, 8, 0, 14321, 0, 0, 0, 0, 0, '', 'Gilneas - Add Phase 4096 after quest 14321 - Forsaken Attacks'),
(25, 4714, 4, 0, 0, 8, 0, 14386, 0, 0, 0, 0, 0, '', 'Gilneas - Remove 4096 after quest 14386 - Remove Forsaken Attack'),
(25, 4714, 7, 0, 0, 8, 0, 14386, 0, 0, 0, 0, 0, '', 'Gilneas - Remove 2 after quest 14386 - Remove Depricated Questgivers after Terrainswap 1'),
(25, 4714, 5, 0, 0, 8, 0, 14386, 0, 0, 0, 0, 0, '', 'Gilneas - After quest 14386 - Terrainswap 1'),
(25, 4714, 8, 0, 0, 8, 0, 14386, 0, 0, 0, 0, 0, '', 'Gilneas - Add Phase 8192 after quest 14386 - Next Duskhaven Quests'),
(25, 4714, 9, 0, 0, 8, 0, 14466, 0, 0, 0, 0, 0, '', 'Gilneas - After quest 14466 - Terrainswap 2'),
(25, 4714, 10, 0, 0, 8, 0, 14466, 0, 0, 0, 0, 0, '', 'Gilneas - Remove 8192 after quest 14466'),
(25, 4714, 11, 0, 0, 8, 0, 14466, 0, 0, 0, 0, 0, '', 'Gilneas - Remove 2048 after quest 14466'),
(25, 4714, 12, 0, 0, 8, 0, 14466, 0, 0, 0, 0, 0, '', 'Gilneas - Add 16384 after quest 14466');

REPLACE INTO `phase_definitions` (`zoneId`, `entry`, `phaseMask`, `terrainswapmap`, `flags`, `comment`) VALUES
(4714, 2, 2048, 0, 0, 'Gilneas - Chapter 2 Add Phase 2048'),
(4714, 3, 4096, 0, 0, 'Gilneas - Chapter 2 Add Phase 4096'),
(4714, 4, 4096, 0, 4, 'Gilneas - Chapter 2 Remove Phase 4096'),
(4714, 5, 0 ,655 , 0, 'Gilneas - Chapter 2 TerrainSwap 1'),
(4714, 6, 2, 0, 0, 'Gilneas - Chapter 2 Add Phase 2'),
(4714, 7, 2, 0, 4, 'Gilneas - Chapter 2 Remove Phase 2'),
(4714, 8, 8192, 0, 0, 'Gilneas - Chapter 2 Add Phase 8192'),
(4714, 9, 0 ,656 , 0, 'Gilneas - Chapter 2 TerrainSwap 2'),
(4714, 10, 2048, 0, 4, 'Gilneas - Chapter 2 Remove Phase 2048'),
(4714, 11, 8192, 0, 4, 'Gilneas - Chapter 2 Remove Phase 8192'),
(4714, 12, 16384, 0, 0, 'Gilneas - Chapter 2 Add Phase 16384');
