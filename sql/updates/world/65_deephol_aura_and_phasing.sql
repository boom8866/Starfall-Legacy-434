
/*
Von    : Hanfblatt
Beschr : Phasing and Auras
Ticket :
*/

DELETE FROM `spell_area` WHERE `spell` = 83322 AND `area` = 5303 AND `quest_start` = 27123;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(83322, 5303, 27123, 26752, 0, 0, 2, 1, 74, 41);

DELETE FROM `spell_area` WHERE `spell` = 84955 AND `area` = 5303 AND `quest_start` = 27123;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(84955, 5303, 27123, 26833, 0, 0, 2, 1, 74, 41);

DELETE FROM `spell_area` WHERE `spell` = 84117 AND `area` = 5303 AND `quest_start` = 27123;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(84117, 5303, 27123, 26326, 0, 0, 2, 1, 74, 41);

DELETE FROM `spell_area` WHERE `spell` = 81032 AND `area` = 5303 AND `quest_start` = 26876;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(81032, 5303, 26876, 26752, 0, 0, 2, 1, 66, 41);

DELETE FROM `spell_area` WHERE `spell` = 83322 AND `area` = 5395 AND `quest_start` = 27123;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(83322, 5395, 27123, 26752, 0, 0, 2, 1, 74, 41);

DELETE FROM `spell_area` WHERE `spell` = 84955 AND `area` = 5395 AND `quest_start` = 27123;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(84955, 5395, 27123, 26833, 0, 0, 2, 1, 74, 41);

DELETE FROM `spell_area` WHERE `spell` = 84117 AND `area` = 5395 AND `quest_start` = 27123;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(84117, 5395, 27123, 26326, 0, 0, 2, 1, 74, 41);

DELETE FROM `spell_area` WHERE `spell` = 81032 AND `area` = 5395 AND `quest_start` = 26876;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(81032, 5395, 26876, 26752, 0, 0, 2, 1, 66, 41);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 17 AND `SourceGroup` = 0 AND `SourceEntry` = 81032;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(17, 0, 81032, 0, 1, 28, 0, 27938, 0, 0, 0, 0, 0, '', NULL),
(17, 0, 81032, 0, 2, 8, 0, 27938, 0, 0, 0, 0, 0, '', NULL);

DELETE FROM `spell_area` WHERE `spell` = 84761 AND `area` = 5300 AND `quest_start` = 26582;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(84761, 5300, 26582, 0, 0, 0, 2, 1, 64, 11);

DELETE FROM `spell_area` WHERE `spell` = 83304 AND `area` = 5395 AND `quest_start` = 26752;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(83304, 5395, 26752, 0, 0, 0, 2, 1, 64, 11);

DELETE FROM `spell_area` WHERE `spell` = 83304 AND `area` = 5303 AND `quest_start` = 26752;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(83304, 5303, 26752, 0, 0, 0, 2, 1, 64, 11);

-- Phasemask update for Maruut Stonebinder (id: 43065) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745520;

-- Phasemask update for Seer Kormo (id: 43397) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745518;

-- Phasemask update for Seer Kormo (id: 43397) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745518;

-- Phasemask update for Earthcaller Yevaa (id: 42573) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745516;

-- Updates the addon of Earthcaller Yevaa ( Entry: 42573 )
UPDATE `creature_template_addon` SET `auras` = '83323 31765' WHERE `entry` = 42573;

-- Phasemask update for Earthmender Narvra (id: 44361) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745521;

-- Phasemask update for Earthmender Govrum (id: 44362) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745522;

-- Phasemask update for Unexploded Artillery Shell (id: 43044) in zone: 5042, area: 5313
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745527;

-- Phasemask update for Flint Oremantle (id: 43036) in zone: 5042, area: 5335
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745515;

-- Phasemask update for Slate Quicksand (id: 47195) in zone: 5042, area: 5357
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745530;

-- Phasemask update for Flint Oremantle (id: 43898) in zone: 5042, area: 5349
UPDATE `creature` SET `phasemask` = 2 WHERE `guid` = 745552;

-- Phasemask update for Bouldergut (id: 44151) in zone: 5042, area: 5350
UPDATE `creature` SET `phasemask` = 4 WHERE `guid` = 745948;

-- Phasemask update for Flint Oremantle (id: 44152) in zone: 5042, area: 5350
UPDATE `creature` SET `phasemask` = 4 WHERE `guid` = 745949;

-- Phasemask update for Stonefather Oremantle (id: 44153) in zone: 5042, area: 5350
UPDATE `creature` SET `phasemask` = 4 WHERE `guid` = 745950;

-- Phasemask update for Stonefather Oremantle (id: 44204) in zone: 5042, area: 5330
UPDATE `creature` SET `phasemask` = 8 WHERE `guid` = 742975;

-- Phasemask update for Flint Oremantle (id: 47197) in zone: 5042, area: 5330
UPDATE `creature` SET `phasemask` = 8 WHERE `guid` = 742973;

-- Phasemask update for Windspeaker Lorvarius (id: 42732) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745768;

-- Phasemask update for Seer Galekk (id: 44222) in zone: 5042, area: 5354
UPDATE `creature` SET `phasemask` = 32 WHERE `guid` = 745134;

-- Phasemask update for Stormcaller Mylra (id: 44010) in zone: 5042, area: 5354
UPDATE `creature` SET `phasemask` = 32 WHERE `guid` = 745136;

-- Phasemask update for Irestone Rumbler (id: 42527) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `id` = 42527;

-- Phasemask update for Earthcaller Torunscar (id: 42730) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 745735;

-- Phasemask update for Earthmender Norsala (id: 42731) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 745734;

-- Phasemask update for Servant of Therazane (id: 42479) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `id` = 42479;

-- Phasemask update for Greater Air Elemental (id: 44363) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `id` = 44363;

-- Phasemask update for Greater Fire Elemental (id: 44364) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `id` = 44364;

-- Phasemask update for Stormcaller Mylra (id: 44353) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 745773;

-- Phasemask update for Tawn Winterbluff (id: 44352) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 745775;

-- Phasemask update for Hargoth Dimblaze (id: 42788) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 745777;

-- Phasemask update for Therazane Siege Arrow Bunny, 3 (id: 47173) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 745776;

-- Phasemask update for Therazane Siege Arrow Bunny, 2 (id: 47172) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 745774;

-- Phasemask update for Therazane Siege Arrow Bunny, 1 (id: 47170) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 745778;

-- Phasemask update for Boden the Imposing (id: 42471) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 745769;

-- Phasemask update for Diamant the Patient (id: 42467) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 741138;

-- Phasemask update for Quartz Stonetender (id: 42899) in zone: 5042, area: 5291
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 741139;

-- Phasemask update for Terrath the Steady (id: 42466) in zone: 5042, area: 5295
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 744166;

-- Phasemask update for Felsen the Enduring (id: 42468) in zone: 5042, area: 5292
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 741418;

-- Phasemask update for Gorsik the Tumultuous (id: 42472) in zone: 5042, area: 5302
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 744874;

-- Phasemask update for Terrath the Steady (id: 42466) in zone: 5042, area: 5295
UPDATE `creature` SET `phasemask` = 64 WHERE `guid` = 744166;

-- Phasemask update for Yuldris Smolderfury (id: 45034) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745672;

-- Phasemask update for Tharm Wildfire (id: 44631) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745673;

-- Phasemask update for Tawn Winterbluff (id: 44634) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745671;

-- Phasemask update for Earthcaller Yevaa (id: 44646) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745670;

-- Phasemask update for Stormcaller Mylra (id: 44642) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 746315;

-- Phasemask update for Hargoth Dimblaze (id: 44644) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 746316;

-- Phasemask update for Stormcaller Jalara (id: 44633) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 746313;

-- Phasemask update for Mariahn the Soulcleanser (id: 44647) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 746314;

-- Phasemask update for Yuldris Smolderfury (id: 45034) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745672;

-- Phasemask update for Tharm Wildfire (id: 44631) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745673;

-- Phasemask update for Tawn Winterbluff (id: 44634) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745671;

-- Phasemask update for Earthcaller Yevaa (id: 44646) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745670;

-- Phasemask update for Stormcaller Mylra (id: 44642) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 746315;

-- Phasemask update for Hargoth Dimblaze (id: 44644) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 746316;

-- Phasemask update for Stormcaller Jalara (id: 44633) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 746313;

-- Phasemask update for Mariahn the Soulcleanser (id: 44647) in zone: 5042, area: 5395
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 746314;

-- Updates the addon of Diamant the Patient ( Entry: 43807 Guid: 745781 )
DELETE FROM `creature_addon` WHERE `guid` = 745781;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(745781, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Therazane ( Entry: 42465 Guid: 744335 )
DELETE FROM `creature_addon` WHERE `guid` = 744335;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744335, 0, 0, 65536, 1, 0, '95366');

-- Updates the addon of Ma'haat the Indomitable ( Entry: 45033 Guid: 744334 )
DELETE FROM `creature_addon` WHERE `guid` = 744334;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744334, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Therazane ( Entry: 42465 Guid: 781420 )
-- DELETE FROM `creature_addon` WHERE `guid` = 781420;
-- INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
-- (781420, 0, 0, 65536, 1, 0, '95366');

-- Updates the addon of Terrath the Steady ( Entry: 43806 Guid: 744340 )
DELETE FROM `creature_addon` WHERE `guid` = 744340;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744340, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Stonetender ( Entry: 44945 Guid: 744336 )
DELETE FROM `creature_addon` WHERE `guid` = 744336;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744336, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Felsen the Enduring ( Entry: 43805 Guid: 744337 )
DELETE FROM `creature_addon` WHERE `guid` = 744337;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744337, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Ma'haat the Indomitable ( Entry: 42470 Guid: 745551 )
DELETE FROM `creature_addon` WHERE `guid` = 745551;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(745551, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Boden the Imposing ( Entry: 42471 Guid: 745780 )
UPDATE `creature_addon` SET `auras` = '80852' WHERE `guid` = 745780;

-- Updates the addon of Earthcaller Torunscar ( Entry: 43809 Guid: 745779 )
DELETE FROM `creature_addon` WHERE `guid` = 745779;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(745779, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Gorsik the Tumultuous ( Entry: 43804 Guid: 744370 )
DELETE FROM `creature_addon` WHERE `guid` = 744370;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744370, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Ruberick ( Entry: 44973 Guid: 744377 )
DELETE FROM `creature_addon` WHERE `guid` = 744377;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744377, 0, 0, 65536, 1, 0, '');

-- Phasemask update for Ma'haat the Indomitable (id: 42470) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745551;

-- Phasemask update for Diamant the Patient (id: 43807) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745781;

-- Updates the addon of Crystalwing Stone Drake ( Entry: 48520 Guid: 744339 )
DELETE FROM `creature_addon` WHERE `guid` = 744339;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744339, 0, 0, 50397184, 1, 0, '');

-- Updates the addon of Crystalwing Stone Drake ( Entry: 48520 Guid: 744338 )
DELETE FROM `creature_addon` WHERE `guid` = 744338;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744338, 0, 0, 50397184, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744320 )
DELETE FROM `creature_addon` WHERE `guid` = 744320;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744320, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744318 )
DELETE FROM `creature_addon` WHERE `guid` = 744318;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744318, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744322 )
DELETE FROM `creature_addon` WHERE `guid` = 744322;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744322, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744324 )
DELETE FROM `creature_addon` WHERE `guid` = 744324;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744324, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744319 )
DELETE FROM `creature_addon` WHERE `guid` = 744319;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744319, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744326 )
DELETE FROM `creature_addon` WHERE `guid` = 744326;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744326, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744321 )
DELETE FROM `creature_addon` WHERE `guid` = 744321;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744321, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744323 )
DELETE FROM `creature_addon` WHERE `guid` = 744323;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744323, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744325 )
DELETE FROM `creature_addon` WHERE `guid` = 744325;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744325, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744317 )
DELETE FROM `creature_addon` WHERE `guid` = 744317;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744317, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744341 )
DELETE FROM `creature_addon` WHERE `guid` = 744341;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744341, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Pyrite Rockling ( Entry: 44947 Guid: 744342 )
DELETE FROM `creature_addon` WHERE `guid` = 744342;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(744342, 0, 0, 65536, 1, 0, '');

-- Updates the addon of Boden the Imposing ( Entry: 42471 Guid: 745780 )
UPDATE `creature_addon` SET `auras` = '' WHERE `guid` = 745780;

-- Phasemask update for Boden the Imposing (id: 42471) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745780;

-- Phasemask update for Earthcaller Torunscar (id: 43809) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745779;

-- Phasemask update for Boden the Imposing (id: 42471) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745780;

-- Phasemask update for Earthcaller Torunscar (id: 43809) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 745779;

-- Phasemask update for Terrath the Steady (id: 42466) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 128 WHERE `guid` = 785421;

-- Phasemask update for Gorsik the Tumultuous (id: 42472) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 128 WHERE `guid` = 785419;

-- Phasemask update for Diamant the Patient (id: 43807) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 128 WHERE `guid` = 745781;

-- Phasemask update for Therazane (id: 42465) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 128 WHERE `guid` = 744335;

-- Phasemask update for Boden the Imposing (id: 42471) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 128 WHERE `guid` = 745780;

-- Phasemask update for Ma'haat the Indomitable (id: 42470) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 128 WHERE `guid` = 745551;

-- Phasemask update for Felsen the Enduring (id: 42468) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 128 WHERE `guid` = 785420;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745790;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745831;

-- Phasemask update for Twilight Pyremaw (id: 42824) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746458;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745895;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745792;

-- Phasemask update for Twilight Pyremaw (id: 42824) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746368;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745920;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745861;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745936;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745894;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745918;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781544;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781546;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781552;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781551;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746279;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746321;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745921;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781538;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781536;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781540;

-- Phasemask update for Terrath the Steady (id: 42614) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745760;

-- Phasemask update for Twilight Pyremaw (id: 44189) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 742608;

-- Phasemask update for Twilight Pyremaw (id: 42824) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746466;

-- Phasemask update for Twilight Pyremaw (id: 44189) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 741523;

-- Phasemask update for Twilight Pyremaw (id: 42824) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746405;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745793;

-- Phasemask update for Twilight Pyremaw (id: 42824) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746397;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745974;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781547;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781548;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781549;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781550;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745767;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745832;

-- Phasemask update for Opal Stonethrower (id: 44124) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745937;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746404;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781554;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781555;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781556;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746365;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745836;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746327;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746480;

-- Phasemask update for Opal Stonethrower (id: 44124) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745893;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745865;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781506;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781507;

-- Phasemask update for Gorsik the Tumultuous (id: 43810) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745763;

-- Phasemask update for Twilight Duskwarden (id: 42917) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 742590;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745898;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781516;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781526;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781441;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781510;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781496;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781438;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781515;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781520;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781442;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781531;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781511;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781513;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781498;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746376;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746447;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781511;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746455;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746474;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746479;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781525;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746376;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746447;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746447;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781511;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781513;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781498;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746474;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745834;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746437;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746427;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746411;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746326;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746415;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746331;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746441;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746442;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746339;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746402;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781576;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781454;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745864;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745863;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745764;

-- Phasemask update for Boldrich Stonerender (id: 42923) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746332;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781443;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745869;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746429;

-- Phasemask update for Twilight Pyremaw (id: 42824) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746328;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746280;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745981;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745955;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746278;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745862;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745919;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781459;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781460;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746384;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746374;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746410;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746310;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746389;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746418;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746432;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746366;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745791;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746343;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781561;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781490;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781489;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781562;

-- Phasemask update for High Priestess Lorthuna (id: 42914) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746255;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745933;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781495;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781503;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781487;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745837;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781468;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781466;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781465;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781467;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745935;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745917;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745827;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781567;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781471;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781474;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781473;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781475;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745828;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746381;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745934;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745866;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745892;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745765;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746377;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746476;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746473;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746388;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746319;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746392;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746358;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746354;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746351;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746308;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746414;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746385;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746309;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746378;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746362;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746352;

-- Phasemask update for Servant of Therazane (id: 44131) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745797;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746360;

-- Phasemask update for Agate Mancrusher (id: 44079) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745867;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746386;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746382;

-- Phasemask update for Servant of Therazane (id: 44131) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745794;

-- Phasemask update for Stone Drake (id: 44077) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745789;

-- Phasemask update for Stone Drake (id: 44077) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745785;

-- Phasemask update for Servant of Therazane (id: 44131) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745795;

-- Phasemask update for Therazane (id: 44025) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745759;

-- Phasemask update for Earthbound Rumbler (id: 44078) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746409;

-- Phasemask update for Boden the Imposing (id: 44080) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745761;

-- Phasemask update for Defaced Earthrager (id: 44076) in zone: 5042, area: 5297
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746355;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781479;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781478;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781477;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781476;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781472;

-- Phasemask update for Twilight Pyremaw (id: 42824) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746438;

-- Phasemask update for Stone Drake (id: 44077) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 745782;

-- Phasemask update for Twilight Pyremaw (id: 42824) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746371;

-- Phasemask update for Stone Drake (id: 44077) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746342;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781493;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781494;

-- Phasemask update for Twilight Soulreaper (id: 42916) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781563;

-- Phasemask update for Stone Drake (id: 44077) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746422;

-- Phasemask update for Twilight Pyremaw (id: 42824) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746357;

-- Phasemask update for Twilight Pyremaw (id: 42824) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746444;

-- Phasemask update for Twilight Pyremaw (id: 42824) in zone: 5042, area: 5298
UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 746369;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781535;

-- Phasemask update for Twilight Priestess (id: 42823) in zone: 5042, area: 5298
-- UPDATE `creature` SET `phasemask` = 256 WHERE `guid` = 781534;

-- Phasemask update for Maruut Stonebinder (id: 43818) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 512 WHERE `guid` = 745753;

-- Phasemask update for Earthmender Govrum (id: 44670) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 512 WHERE `guid` = 745748;

-- Phasemask update for Earthcaller Torunscar (id: 43835) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 512 WHERE `guid` = 745749;

-- Phasemask update for Earthmender Narvra (id: 44669) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 512 WHERE `guid` = 745755;

-- Phasemask update for Earthmender Norsala (id: 44666) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 512 WHERE `guid` = 745754;

-- Phasemask update for Gorsik the Tumultuous (id: 44679) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745679;

-- Phasemask update for Ma'haat the Indomitable (id: 44830) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745677;

-- Phasemask update for Windspeaker Lorvarius (id: 44677) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745931;

-- Phasemask update for Earthcaller Yevaa (id: 44676) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745879;

-- Phasemask update for Mariahn the Soulcleanser (id: 44678) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745844;

-- Phasemask update for Seer Galekk (id: 44668) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745873;

-- Phasemask update for Hargoth Dimblaze (id: 44675) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745923;

-- Phasemask update for Stormcaller Mylra (id: 44673) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745839;

-- Adds creature Nom (id: 43818) in zone: 5042, area: 5303
DELETE FROM `creature` WHERE `guid` = 785907;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(785907, 43818, 646, 15, 1, 997.071716, 521.500183, -49.334354, 0.175049, 300, 2147483647, 9757);

-- Phasemask update for Maruut Stonebinder (id: 43818) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 785907;

-- Phasemask update for Therazane (id: 43792) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745899;

-- Phasemask update for Tharm Wildfire (id: 44671) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745927;

-- Phasemask update for Earthmender Norsala (id: 44666) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745840;

-- Phasemask update for Tawn Winterbluff (id: 44674) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745926;

-- Phasemask update for Earthcaller Torunscar (id: 43835) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745847;

-- Phasemask update for Earthmender Narvra (id: 44669) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745682;

-- Phasemask update for Seer Kormo (id: 44667) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745900;

-- Position update for Therazane (id: 43792) in zone: 5042, area: 5303
UPDATE `creature` SET `position_x` = 978.203, `position_y` = 517.083, `position_z` = -49.334, `orientation`= 0.201 WHERE `guid` = 745899;

-- Position update for Gorsik the Tumultuous (id: 44679) in zone: 5042, area: 5303
UPDATE `creature` SET `position_x` = 991.207, `position_y` = 549.297, `position_z` = -49.334, `orientation`= 5.472 WHERE `guid` = 745679;

-- Phasemask update for Earthmender Govrum (id: 44670) in zone: 5042, area: 5303
UPDATE `creature` SET `phasemask` = 1024 WHERE `guid` = 745845;

-- Phasemask update for Felsen the Enduring (id: 43805) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 2048 WHERE `guid` = 744337;

-- Phasemask update for Ma'haat the Indomitable (id: 45033) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 2048 WHERE `guid` = 744334;

-- Phasemask update for Terrath the Steady (id: 43806) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 2048 WHERE `guid` = 744340;

-- Phasemask update for Therazane (id: 42465) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 2176 WHERE `guid` = 744335;

-- Phasemask update for Gorsik the Tumultuous (id: 43804) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 2048 WHERE `guid` = 744370;

-- Phasemask update for Ruberick (id: 44973) in zone: 5042, area: 5296
UPDATE `creature` SET `phasemask` = 2048 WHERE `guid` = 744377;


DELETE FROM `phase_definitions` WHERE `zoneId` = 5042 AND `entry` IN (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19);
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `phaseId`, `terrainswapmap`, `flags`, `comment`) VALUES 
(5042, 1, 3, 0, 0, 0, 'Deepholm: Add Phase 3 After Reward Quest: Take Him to the Earthcaller 26413'),
(5042, 2, 5, 0, 0, 0, 'Deepholm: Add Phase 5 After Reward Quest: Down Into the Chasm 26834'),
(5042, 3, 2, 0, 0, 4, 'Deepholm: Negate Phase 3 After Reward Quest: Down Into the Chasm 26834'),
(5042, 4, 9, 0, 0, 0, 'Deepholm: Add Phase 9 After Reward Quest: Rescue the Stonefather... and Flint 26836'),
(5042, 5, 4, 0, 0, 4, 'Deepholm: Negate Phase 5 After Reward Quest: Rescue the Stonefather... and Flint 26836'),
(5042, 6, 17, 0, 0, 0, 'Deepholm: Add Phase 17 After Reward Quest: Captains Log 26246'),
(5042, 7, 33, 0, 0, 0, 'Deepholm: Add Phase 33 After Reward Quest: Quicksilver Submersion 27010'),
(5042, 8, 16, 0, 0, 4, 'Deepholm: Negate Phase 17 After Reward Quest: Quicksilver Submersion 27010'),
(5042, 9, 65, 0, 0, 0, 'Deepholm: Add Phase 65 After Complete OR Reward Quest: 27938 and 26876'),
(5042, 10, 32, 0, 0, 4, 'Deepholm: Negate Phase 32 After Taken OR Reward Quest: 26326'),
(5042, 11, 64, 0, 0, 4, 'Deepholm: Negate Phase 64 After Reward Quest: 26750'),
(5042, 12, 129, 0, 0, 0, 'Deepholm: Add Phase 128 After Complete OR Reward Quest: 26750'),
(5042, 13, 128, 0, 0, 4, 'Deepholm: Negate Phase 128 After Reward Quest: 26827'),
(5042, 14, 257, 0, 0, 0, 'Deepholm: Add Phase 526 After Reward Quest: 26827'),
(5042, 15, 256, 0, 0, 4, 'Deepholm: Negate Phase 256 After Reward Quest: 26833'),
(5042, 16, 513, 0, 0, 0, 'Deepholm: Add Phase 512 After Complete OR Reward Quest: 26833'),
(5042, 17, 512, 0, 0, 4, 'Deepholm: Negate Phase 512 After Reward Quest: 26971'),
(5042, 18, 1025, 0, 0, 0, 'Deepholm: Add Phase 1024 After Reward Quest: 26971'),
(5042, 19, 2049, 0, 0, 0, 'Deepholm: Add Phase 1024 After Complete OR Reward Quest: 26709');

-- Condition for Phasedefinition Quest rewarded
SET @ZONE := 5042;
SET @ENTRY := 1;
SET @QUEST := 26413;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 2;
SET @QUEST := 26834;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 3;
SET @QUEST := 26834;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 4;
SET @QUEST := 26836;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 5;
SET @QUEST := 26836;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 6;
SET @QUEST := 26246;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 7;
SET @QUEST := 27010;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 8;
SET @QUEST := 27010;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

-- 2 Rewarded
SET @ZONE := 5042;
SET @ENTRY := 9;
SET @QUEST := 27938;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 9;
SET @QUEST := 26876;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

-- 2 Completed
SET @ZONE := 5042;
SET @ENTRY := 9;
SET @QUEST := 27938;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 2, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 9;
SET @QUEST := 26876;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 2, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

-- 1 Rewarded and 1 Completed
SET @ZONE := 5042;
SET @ENTRY := 9;
SET @QUEST := 27938;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 3, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 9;
SET @QUEST := 26876;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 3, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 9;
SET @QUEST := 26876;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 4, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 9;
SET @QUEST := 27938;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 4, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 10;
SET @QUEST := 26326;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 10;
SET @QUEST := 26326;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 2, 9, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 10;
SET @QUEST := 26326;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 3, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 11;
SET @QUEST := 26750;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 12;
SET @QUEST := 26750;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 12;
SET @QUEST := 26750;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 2, 9, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 12;
SET @QUEST := 26750;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 3, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 13;
SET @QUEST := 26827;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 14;
SET @QUEST := 26827;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 15;
SET @QUEST := 26833;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 16;
SET @QUEST := 26833;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 16;
SET @QUEST := 26833;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 2, 9, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 16;
SET @QUEST := 26833;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 3, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 17;
SET @QUEST := 26971;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 18;
SET @QUEST := 26971;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 19;
SET @QUEST := 26709;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 19;
SET @QUEST := 26709;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 2, 9, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

SET @ZONE := 5042;
SET @ENTRY := 19;
SET @QUEST := 26709;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 3, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', '');