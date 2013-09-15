DELETE FROM `creature_text` WHERE `entry` = '2981';
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES (2981, 0, 0, 'Earth Mother, into your arms we give one of our own. She is Unaya Hawkwind, my mother, and Greatmother to us all; the wisest of our tribe.', 12, 0, 100, 16, 0, 0, 'Chief Hawkwind');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES (2981, 1, 0, 'May her spirit fly to you swiftly; may the winds carry her gently, and the grass whisper her name.', 12, 0, 100, 16, 0, 0, 'Chief Hawkwind');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES (2981, 2, 0, 'Watch over her as she has watched over us; let her look down on us with joy, through the eternal gaze of An\'she and Mu\'sha, until we too join her in death.', 12, 0, 100, 1, 0, 0, 'Chief Hawkwind');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES (2981, 3, 0, 'For we are all born of you, and shall all return to you.', 12, 0, 100, 1, 0, 0, 'Chief Hawkwind');

UPDATE `creature_template` SET `ScriptName`='npc_chief_hawkwind' WHERE  `entry`=2981;

DELETE FROM `spell_script_names` WHERE `spell_id` = '71898';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (71898, 'spell_funeral_offering');