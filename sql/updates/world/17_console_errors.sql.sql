-- Remove Uneeded Transport objects
DELETE FROM `gameobject_template` WHERE `entry` IN(21653, 21654, 21655, 21656, 32056, 32057, 80024, 176086, 192517, 193458, 193459, 193460, 193461, 194030, 194031, 194582, 194583, 194584, 194585, 194586, 194587);

-- Update missing portal spells
UPDATE `gameobject_template` SET `data0` = 85891 WHERE `entry` = 205876;
UPDATE `gameobject_template` SET `data0` = 85892 WHERE `entry` = 205877;
UPDATE `gameobject_template` SET `data0` = 96364 WHERE `entry` = 208325;
-- Missing dbc data (custom stuffs)
DELETE FROM `spell_dbc` WHERE `Id` IN(85891,85892,96364);
INSERT INTO `spell_dbc` (`Id`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, `AttributesEx4`, `AttributesEx5`, `AttributesEx6`, `AttributesEx7`, `AttributesEx8`, `AttributesEx9`, `AttributesEx10`, `CastingTimeIndex`, `DurationIndex`, `RangeIndex`, `SchoolMask`, `SpellAuraOptionsId`, `SpellCastingRequirementsId`, `SpellCategoriesId`, `SpellClassOptionsId`, `SpellEquippedItemsId`, `SpellLevelsId`, `SpellTargetRestrictionsId`, `SpellInterruptsId`, `Comment`) VALUES
('85891', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '38', '0', '0', '0', '0', '0', '0', '0', 'Teleport to ??? serverside spell'),
('85892', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '38', '0', '0', '0', '0', '0', '0', '0', 'Teleport to ??? serverside spell'),
('96364', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '38', '0', '0', '0', '0', '0', '0', '0', 'serverside spell for gobjid=208325');

-- Id: 59620
-- Name: Berserk IT'S NOT A SPELL PROC
DELETE FROM `spell_proc_event` WHERE `entry` = 59620;
-- Wrong Creature Class
UPDATE `creature_template` SET `unit_class` = 2 WHERE `entry` IN(49093,49107,50105,49610,50113,50108,57771,57955,58250,37615, 37617, 37619, 37621, 37632, 37654, 48677, 48710, 48744, 48753, 48776, 48784, 48814, 48936, 48951, 49043, 49262, 49292, 49295, 49300, 49308, 49310, 49324, 49325, 49326, 49328, 49330, 49504, 49505, 49507, 49508, 49509, 49510, 49511, 49512, 49609, 49664, 49665, 49744, 50095, 50098, 50103, 51088, 52393, 52395, 57292, 57294, 57409, 57462, 57463, 57808, 57818, 57820, 57822, 57824);
UPDATE `creature_template` SET `unit_class` = 4 WHERE `entry` IN (49057,49048,48715, 48791, 48803, 48804, 48941, 49047, 49056, 49293, 57293);
UPDATE `creature_template` SET `unit_class` = 8 WHERE `entry` IN (48792,37630, 48595, 48597, 48652, 48653, 48669, 48695, 48745, 48746, 48748, 48750, 48778, 48812, 49317, 49318, 49320, 49653, 49662, 57296);

-- Some wrong creature npcflag
UPDATE `creature_template` SET `npcflag` = 2 WHERE `entry` IN (37632,37630,49624,49648,48941,48936,48940,48943,48944);
UPDATE `creature_template` SET `npcflag` = 1 WHERE `entry` IN (46224,46225);
UPDATE `creature_template` SET `npcflag` = 3 WHERE `entry` = 57481;
UPDATE `creature_template` SET `npcflag` = 256 WHERE `entry` = 47036;
UPDATE `creature_template` SET `npcflag` = 16777216 WHERE `entry` IN (48804,48803,48913);

-- Delete Wrong difficulty_entry_1 entry
UPDATE `creature_template` SET `difficulty_entry_1`='0' WHERE `entry`='40622';
UPDATE `creature_template` SET `difficulty_entry_1`='48792' WHERE `entry`='48417';
UPDATE `creature_template` SET `difficulty_entry_1`='49093' WHERE `entry`='44404';
UPDATE `creature_template` SET `difficulty_entry_1`='49096' WHERE `entry`='40655';

UPDATE `creature_template_addon` SET `auras`=NULL WHERE `entry`='44566';