
-- Quest Hyjal

-- Nordrassil
-- Protect the World Tree
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 25472, NextQuestIdChain = 25472 WHERE id = 25317;

-- War on the Twilight's Hammer (Optional)
UPDATE quest_template SET PrevQuestId = 25317, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25319;

-- The Flameseer's Staff
UPDATE quest_template SET PrevQuestId = 25317, NextQuestId = 25323, NextQuestIdChain = 25323 WHERE id = 25472;

-- Flamebreaker
UPDATE quest_template SET PrevQuestId = 25472, NextQuestId = 25464, NextQuestIdChain = 25464 WHERE id = 25323;

-- The Return of Baron Geddon
UPDATE quest_template SET PrevQuestId = 25323, NextQuestId = 25430, NextQuestIdChain = 25430 WHERE id = 25464;

-- Emerald Allies
UPDATE quest_template SET PrevQuestId = 25464, NextQuestId = 25320, NextQuestIdChain = 25320 WHERE id = 25430;

-- The Captured Shout
UPDATE quest_template SET PrevQuestId = 25430, NextQuestId = 25321, NextQuestIdChain = 25321 WHERE id = 25320;

-- Twilight Captivity
UPDATE quest_template SET PrevQuestId = 25320, NextQuestId = 25424, NextQuestIdChain = 25424 WHERE id = 25321;

-- Return to Alysra
UPDATE quest_template SET PrevQuestId = 25321, NextQuestId = 25324, NextQuestIdChain = 25324 WHERE id = 25424;

-- A Prisoner of Interest
UPDATE quest_template SET PrevQuestId = 25424, NextQuestId = 25325, NextQuestIdChain = 25325 WHERE id = 25324;

-- Through the Dream
UPDATE quest_template SET PrevQuestId = 25324, NextQuestId = 25578, NextQuestIdChain = 25578 WHERE id = 25325;

-- Return to Nordrassil
UPDATE quest_template SET PrevQuestId = 25325, NextQuestId = 25584, NextQuestIdChain = 25584 WHERE id = 25578;

-- Wings Over Mount Hyjal (Optional)
UPDATE quest_template SET PrevQuestId = 25578, NextQuestId = 25663, NextQuestidChain = 25663, ExclusiveGroup = 27874 WHERE id = 25985;

-- Scrambling for Eggs (Optional)
UPDATE quest_template SET PrevQuestId = 25578, NextQuestId = 25731, NextQuestIdChain = 25731, ExclusiveGroup = '-25655' WHERE id = 25656;

-- The Wormwing Problem (Optional)
UPDATE quest_template SET PrevQuestId = 25578, NextQuestId = 25731, NextQuestIdChain = 25731, ExclusiveGroup = '-25655' WHERE id = 25655;

-- The Return of the Ancients
UPDATE quest_template SET PrevQuestId = 25578, NextQuestId = 25255, NextQuestIdChain = 25255, ExclusiveGroup = '0' WHERE id = 25584;

-- In the Rear With the Gear
UPDATE quest_template SET PrevQuestId = 25584, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25234;

-- End of the Supply Line
UPDATE quest_template SET PrevQuestId = 25584, NextQuestId = 25268, NextQuestIdChain = 25268 WHERE id = 25233;

-- Harrying the Hunters
UPDATE quest_template SET PrevQuestId = 25584, NextQuestId = 25269, NextQuestIdChain = 25269 WHERE id = 25255;

-- The Voice of Goldrinn (Alliance)
UPDATE quest_template SET PrevQuestId = 25233, NextQuestId = 25271, NextQuestIdChain = 25271 WHERE id = 25268;

-- The Voice of Lo'Gosh (Horde)
UPDATE quest_template SET PrevQuestId = 25255, NextQuestId = 25270, NextQuestIdChain = 25270 WHERE id = 25269;

-- Goldrinn's Ferocity (Alliance)
UPDATE quest_template SET PrevQuestId = 25268, NextQuestId = 25273, NextQuestIdChain = 25273 WHERE id = 25271;

-- Howling Mad (Horde)
UPDATE quest_template SET PrevQuestId = 25269, NextQuestId = 25272, NextQuestIdChain = 25272 WHERE id = 25270;

-- Seperate Questline
-- The Eye of Twilight (Optional)
UPDATE quest_template SET PrevQuestId = '25273 25272', NextQuestId = 25301, NextQuestIdChain = 25301 WHERE id = 25300;
/*REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `Sourceid`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
('19', '0', '25300', '0', '0', '8', '0', '25270', '0', '0', '0', '0', '0', '', '(H) Hyjal - Quest 25300 accept on reward Quest 25270 or'),
('19', '0', '25300', '0', '1', '8', '0', '25271', '0', '0', '0', '0', '0', '', '(A) Hyjal - Quest 25300 accept on reward Quest 25271'),
('18', '0', '25300', '0', '0', '8', '0', '25270', '0', '0', '0', '0', '0', '', '(H) Hyjal - Quest 25300 show mark on reward Quest 25270 or'),
('18', '0', '25300', '0', '1', '8', '0', '25271', '0', '0', '0', '0', '0', '', '(A) Hyjal - Quest 25300 show mark on reward Quest 25271');*/

-- Mastering Puppets (Optional)
UPDATE quest_template SET PrevQuestId = 25300, NextQuestId = 25303, NextQuestIdChain = 25303 WHERE id = 25301;

-- Elementary! (Optional)
UPDATE quest_template SET PrevQuestId = 25301, NextQuestId = 25312, NextQuestIdChain = 25312 WHERE id = 25303;

-- Return to Duskwhisper (Optional)
UPDATE quest_template SET PrevQuestId = 25303, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25312;

-- From the Mouth of Madness (Optional)
UPDATE quest_template SET PrevQuestId = '25273 25272', NextQuestId = 25298, NextQuestIdChain = 25298 WHERE id = 25297;
/*REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `Sourceid`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
('19', '0', '25297', '0', '0', '8', '0', '25270', '0', '0', '0', '0', '0', '', '(H) Hyjal - Quest 25297 accept on reward Quest 25270 or'),
('19', '0', '25297', '0', '1', '8', '0', '25271', '0', '0', '0', '0', '0', '', '(A) Hyjal - Quest 25297 accept on reward Quest 25271'),
('18', '0', '25297', '0', '0', '8', '0', '25270', '0', '0', '0', '0', '0', '', '(H) Hyjal - Quest 25297 show mark on reward Quest 25270 or'),
('18', '0', '25297', '0', '1', '8', '0', '25271', '0', '0', '0', '0', '0', '', '(A) Hyjal - Quest 25297 show mark on reward Quest 25271');*/

-- Free Your Mind, the Rest Follows (Optional)
UPDATE quest_template SET PrevQuestId = 25297, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25298;

-- Gar'gol's Gotta Go (Optional)
UPDATE quest_template SET PrevQuestId = '0', NextQuestId = 25332, NextQuestIdChain = 25332 WHERE id = 25328;

-- Get Me Outta Here! (Optional)
UPDATE quest_template SET PrevQuestId = 25328, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25332;

-- Lycanthoth the Corruptor (Alliance)
UPDATE quest_template SET PrevQuestId = 25271, NextQuestId = 25280, NextQuestIdChain = 25280 WHERE id = 25273;

-- Lycanthoth the Corruptor (Horde)
UPDATE quest_template SET PrevQuestId = 25270, NextQuestId = 25279, NextQuestIdChain = 25279 WHERE id = 25272;

-- The Shrine Reclaimed (Alliance)
UPDATE quest_template SET PrevQuestId = 25273, NextQuestId = 25278, NextQuestIdChain = 25278 WHERE id = 25280;

-- The Shrine Reclaimed (Horde)
UPDATE quest_template SET PrevQuestId = 25272, NextQuestId = 25277, NextQuestIdChain = 25277 WHERE id = 25279;

-- Cleaning House (Alliance)
UPDATE quest_template SET PrevQuestId = 25280, NextQuestId = 25353, NextQuestIdChain = 25353 WHERE id = 25278;

-- Cleaning House (Horde)
UPDATE quest_template SET PrevQuestId = 25279, NextQuestId = 25355, NextQuestIdChain = 25355 WHERE id = 25277;

-- Sweeping the Shelf (Alliance)
UPDATE quest_template SET PrevQuestId = 25278, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25352;

-- Sweeping the Shelf (Horde)
UPDATE quest_template SET PrevQuestId = 25277, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25354;

-- Lightning in a Bottle (Alliance)
UPDATE quest_template SET PrevQuestId = 25278, NextQuestId = 25618, NextQuestIdChain = 25618 WHERE id = 25353;

-- Lightning in a Bottle (Horde)
UPDATE quest_template SET PrevQuestId = 25277, NextQuestId = 25617, NextQuestIdChain = 25617 WHERE id = 25355;

-- Into the Maw! (Alliance 1 and Alliance 2)
UPDATE quest_template SET PrevQuestId = 25353, NextQuestId = 0, NextQuestIdChain = 0, ExclusiveGroup = 25618 WHERE id IN (25618, 25623);

-- Into the Maw! (Horde 1 and Horde 2)
UPDATE quest_template SET PrevQuestId = 25355, NextQuestId = 0, NextQuestIdChain = 0, ExclusiveGroup = 25617 WHERE id IN (25617, 25624);

-- Forged of Shadow and Flame
-- Crushing the Cores
-- Rage of the Wolf Ancient
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 25599, NextQuestIdChain = 0, ExclusiveGroup = '-25575' WHERE id IN (25575, 25577, 25576);

-- Cindermaul, the Portal Master
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 25600, NextQuestIdChain = 25600 WHERE id = 25599;

-- Forgemaster Pyrendius
UPDATE quest_template SET PrevQuestId = 25599, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25600;

-- Return from the Firelands (Alliance)
UPDATE quest_template SET PrevQuestId = 25600, NextQuestId = 0, NextQuestIdChain = 0, ExclusiveGroup = '0' WHERE id = 25611;

-- Return from the Firelands (Horde)
UPDATE quest_template SET PrevQuestId = 25600, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25612;

-- The Fires of Mount Hyjal
UPDATE quest_template SET PrevQuestId = '25611 25612', NextQuestId = 25381, NextQuestIdChain = 25381, ExclusiveGroup = '0' WHERE id = 25630;

-- Fighting Fire With ... Anything
UPDATE quest_template SET PrevQuestId = 25630, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25381;

-- Aviana's Legacy
UPDATE quest_template SET PrevQuestId = '25611 25612', NextQuestId = 25663, NextQuestIdChain = 25663, ExclusiveGroup = 27874 WHERE id = 27874;

-- An Offering for Aviana (Optional)
UPDATE quest_template SET PrevQuestId = '27874 25985', NextQuestId = 25665, NextQuestIdChain = 25665 WHERE id = 25663;

-- A Plea From Beyond (Optional)
UPDATE quest_template SET PrevQuestId = 25663, NextQuestId = 25664, NextQuestIdChain = 25664 WHERE id = 25665;

-- A Prayer and a Wing (Optional)
UPDATE quest_template SET PrevQuestId = 25665, NextQuestId = 25740, NextQuestIdChain = 0, ExclusiveGroup = '-25731' WHERE id = 25664;

-- A Bird in Hand
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 25740, NextQuestIdChain = 0, ExclusiveGroup = '-25731' WHERE id = 25731;

-- Fact-Finding Mission
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 25746, NextQuestIdChain = 25746 WHERE id = 25740;

-- Sehria's Brood
UPDATE quest_template SET PrevQuestId = 25740, NextQuestId = 25776, NextQuestIdChain = 0, ExclusiveGroup = '-25746' WHERE id = 25746;

-- The Codex of Shadows
UPDATE quest_template SET PrevQuestId = 25740, NextQuestId = 25764, NextQuestIdChain = 25764 WHERE id = 25763;

-- A Gap in Their Armor
UPDATE quest_template SET PrevQuestId = 25740, NextQuestId = 25761, NextQuestIdChain = 25761 WHERE id = 25758;

-- Egg Hunt
UPDATE quest_template SET PrevQuestId = 25763, NextQuestId = 25776, NextQuestIdChain = 0, ExclusiveGroup = '-25746' WHERE id = 25764;

-- Disassembly
UPDATE quest_template SET PrevQuestId = 25758, NextQuestId = 25776, NextQuestIdChain = 0, ExclusiveGroup = '-25746' WHERE id = 25761;

-- Sethria's Demise
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 25795, NextQuestIdChain = 25795 WHERE id = 25776;

-- Return to the Shrine
UPDATE quest_template SET PrevQuestId = 25776, NextQuestId = 25807, NextQuestIdChain = 25807 WHERE id = 25795;

-- An Ancient Reborn
UPDATE quest_template SET PrevQuestId = 25795, NextQuestId = 25830, NextQuestIdChain = 0, ExclusiveGroup = '-25807' WHERE id = 25807;

-- The Hatchery Must Burn
UPDATE quest_template SET PrevQuestId = 25807, NextQuestId = 25523, NextQuestIdChain = 25523 WHERE id = 25810;

-- Flight in the Firelands
UPDATE quest_template SET PrevQuestId = 25810, NextQuestId = 25525, NextQuestIdChain = 25525 WHERE id = 25523;

-- Wave On
UPDATE quest_template SET PrevQuestId = 25523, NextQuestId = 25544, NextQuestIdChain = 25544 WHERE id = 25525;

-- Wave Two
UPDATE quest_template SET PrevQuestId = 25525, NextQuestId = 25560, NextQuestIdChain = 25560 WHERE id = 25544;

-- Egg Wave
UPDATE quest_template SET PrevQuestId = 25544, NextQuestId = 25832, NextQuestIdChain = 25832 WHERE id = 25560;

-- Return to Aviana
UPDATE quest_template SET PrevQuestId = 25560, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25832;

-- Save the Wee Animals
UPDATE quest_template SET PrevQuestId = 25584, NextQuestId = 25392, NextQuestIdChain = 25392 WHERE id = 25385;

-- If You're Not Against Us
UPDATE quest_template SET PrevQuestId = 25584, NextQuestId = 25408, NextQuestIdChain = 25408 WHERE id = 25404;

-- Seeds of Their Demise
UPDATE quest_template SET PrevQuestId = 25404, NextQuestId = 25411, NextQuestIdChain = 25411 WHERE id = 25408;

-- A New Master
UPDATE quest_template SET PrevQuestId = 25408, NextQuestId = 25412, NextQuestIdChain = 25412 WHERE id = 25411;

-- The Name Never Spoken
UPDATE quest_template SET PrevQuestId = 25411, NextQuestId = 25428, NextQuestIdChain = 25428 WHERE id = 25412;

-- Black Heart of Flame
UPDATE quest_template SET PrevQuestId = 25412, NextQuestId = 25940, NextQuestIdChain = 0, ExclusiveGroup = '-25382' WHERE id = 25428;

-- Disrupting the Rituals
UPDATE quest_template SET PrevQuestId = 25584, NextQuestId = 25940, NextQuestIdChain = 0, ExclusiveGroup = '-25382' WHERE id = 25382;

-- Oh, Deer!
UPDATE quest_template SET PrevQuestId = 25385, NextQuestId = 25940, NextQuestIdChain = 0, ExclusiveGroup = '-25382' WHERE id = 25392;

-- Last Stand at Whistling Grove
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 25462, NextQuestIdChain = 25462 WHERE id = 25940;

-- The Bears Up There
UPDATE quest_template SET PrevQuestId = 25940, NextQuestId = 25490, NextQuestIdChain = 25490 WHERE id = 25462;

-- Smashing Through Ashes
UPDATE quest_template SET PrevQuestId = 25462, NextQuestId = 25491, NextQuestIdChain = 25491 WHERE id = 25490;

-- Firebreak
UPDATE quest_template SET PrevQuestId = 25490, NextQuestId = 25502, NextQuestIdChain = 25502 WHERE id = 25492;

-- Prepping the Soil
UPDATE quest_template SET PrevQuestId = 25492, NextQuestId = 0, NextQuestIdChain = 0, ExclusiveGroup = '0' WHERE id = 25502;

-- Durable Seeds
UPDATE quest_template SET PrevQuestId = 25490, NextQuestId = 0, NextQuestIdChain = 0, ExclusiveGroup = '0' WHERE id = 25491;

-- Fresh Bait
UPDATE quest_template SET PrevQuestId = 25490, NextQuestId = 25507, NextQuestIdChain = 25507 WHERE id = 25493;

-- Hell's Shells
UPDATE quest_template SET PrevQuestId = 25493, NextQuestId = 25510, NextQuestIdChain = 25510 WHERE id = 25507;

-- Tortolla Speaks
UPDATE quest_template SET PrevQuestId = 25507, NextQuestId = 25514, NextQuestIdChain = 0 WHERE id = 25510;

-- Breaking the Bonds
UPDATE quest_template SET PrevQuestId = 25510, NextQuestId = 25520, NextQuestIdChain = 0, ExclusiveGroup = '-25514' WHERE id = 25514;

-- Children of Tortolla
UPDATE quest_template SET PrevQuestId = 25510, NextQuestId = 25520, NextQuestIdChain = 0, ExclusiveGroup = '-25514' WHERE id = 25519;

-- An Ancient Awakens
UPDATE quest_template SET PrevQuestId = 0, NextQuestId = 25830, NextQuestIdChain = 0, ExclusiveGroup = '-25807' WHERE id = 25520;

-- The Last Living Lorekeeper
UPDATE quest_template SET PrevQuestId = '25611 25612', NextQuestId = 25842, NextQuestIdChain = 25842 WHERE id = 25830;

-- Firefight
UPDATE quest_template SET PrevQuestId = 25830, NextQuestId = 25372, NextQuestIdChain = 25372 WHERE id = 25842;

-- Aessina's Miracle
UPDATE quest_template SET PrevQuestId = 25842, NextQuestId = 25843, NextQuestIdChain = 25843 WHERE id = 25372;

-- Hyjal Recycling Program
UPDATE quest_template SET PrevQuestId = 25372, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25901;

-- Lost Wardens
UPDATE quest_template SET PrevQuestId = 25372, NextQuestId = 25886, NextQuestIdChain = 25886 WHERE id = 25881;

-- Pressing the Advantage
UPDATE quest_template SET PrevQuestId = 25881, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25886;

-- Tortolla's Revenge
UPDATE quest_template SET PrevQuestId = 25372, NextQuestId = 25904, NextQuestIdChain = 25904 WHERE id = 25843;

-- Breakthrough
UPDATE quest_template SET PrevQuestId = 25843, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25899;

-- The Hammer and the Key
UPDATE quest_template SET PrevQuestId = 25843, NextQuestId = 25906, NextQuestIdChain = 25906 WHERE id = 25904;

-- The Third Flamegate
UPDATE quest_template SET PrevQuestId = 25904, NextQuestId = 25915, NextQuestIdChain = 25915 WHERE id = 25906;

-- The Time for Mercy has Passed
UPDATE quest_template SET PrevQuestId = 25906, NextQuestId = 0, NextQuestIdChain = 0 WHERE id = 25910;

-- The Strength of Tortolla
UPDATE quest_template SET PrevQuestId = 25906, NextQuestId = 25923, NextQuestIdChain = 25923 WHERE id = 25915;

-- Finish Nemesis
UPDATE quest_template SET PrevQuestId = 25915, NextQuestId = 25928, NextQuestIdChain = 25928 WHERE id = 25923;

-- Tortolla's Triumph
UPDATE quest_template SET PrevQuestId = 25923, NextQuestId = 25653, NextQuestIdChain = 25653 WHERE id = 25928;

-- The Ancients are With Us
UPDATE quest_template SET PrevQuestId = 25928, NextQuestId = 25597, NextQuestIdChain = 25597 WHERE id = 25653;

-- In Bloom
UPDATE `quest_template` SET `PrevQuestId`='25276', `NextQuestId`='25291', `ExclusiveGroup`=-25223 WHERE  `Id`=25224;

-- Trial By Fire
UPDATE `quest_template` SET `PrevQuestId`='25276', `NextQuestId`='25291', `ExclusiveGroup`=-25223 WHERE  `Id`=25223;

-- Waste of Flesh
UPDATE `quest_template` SET `PrevQuestId`='25276', `NextQuestId`='25291', `ExclusiveGroup`=-25223 WHERE  `Id`=25330;

-- Walking the Dog
UPDATE `quest_template` SET `PrevQuestId`='25291' WHERE  `Id`=25294;

-- Gather the Intellegence
UPDATE `quest_template` SET `PrevQuestId`='25291' WHERE  `Id`=25296;

-- Mental Training: Speaking the Truth to Power
UPDATE `quest_template` SET `PrevQuestId`='25499' WHERE  `Id`=25299;

-- Spiritual Training: Mercy is for the Weak
UPDATE `quest_template` SET `PrevQuestId`='25299', `NextQuestId`='25311 25310', `ExclusiveGroup`=-25309 WHERE  `Id`=25309;

-- Grudge Match
UPDATE `quest_template` SET `PrevQuestId`='25494', `NextQuestId`='25311 25310', `ExclusiveGroup`=-25309 WHERE  `Id`=25496;

-- Seeds of Discord
UPDATE `quest_template` SET `NextQuestId`='25314', `ExclusiveGroup`=-25308 WHERE  `Id`=25308;

-- The Greater of Two Evils 
UPDATE `quest_template` SET `NextQuestId`='25314', `ExclusiveGroup`=-25308 WHERE  `Id`=25310;

-- Twilight Territory
UPDATE `quest_template` SET `NextQuestId`='25314', `ExclusiveGroup`=-25308 WHERE  `Id`=25311;

-- Head of the Class
UPDATE `quest_template` SET `PrevQuestId`='25314' WHERE  `Id`=25601;

-- The Battle Is Won, The War Goes On{H}
UPDATE `quest_template` SET `PrevQuestId`='25551' WHERE  `Id`=27398;
UPDATE `quest_template` SET `PrevQuestId`='25551' WHERE  `Id`=27399;

-- Secrets of the Flame
UPDATE `quest_template` SET `PrevQuestId`='25608' WHERE  `Id`=25554;

-- The Firelord
UPDATE `quest_template` SET `PrevQuestId`='0' WHERE  `Id`=25551;

-- Death to the Broodmother
UPDATE `quest_template` SET `NextQuestId`='25551', `ExclusiveGroup`=-25550 WHERE  `Id`=25553;

-- The Gatekeeper
UPDATE `quest_template` SET `NextQuestId`='25551', `ExclusiveGroup`=-25550 WHERE  `Id`=25555;

-- Magma Monarch
UPDATE `quest_template` SET `NextQuestId`='25551', `ExclusiveGroup`=-25550 WHERE  `Id`=25550;