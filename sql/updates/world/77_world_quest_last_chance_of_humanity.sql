UPDATE `creature_template` SET `scriptname`= 'npc_godfrey_qls' WHERE `entry`= 36330;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(36331, 0, 0, 'I am not giving up on you.  I don''t have a cure for the Curse yet... but there are treatments.  You will have control again.', 12, 0, 100, 0, 274, 20919, 'Krennan - Chapter 2 Intro'),
(36330, 0, 0, 'Give it up, Krennan.  It''s time to put this one down.  It''s protocol.', 12, 0, 100, 0, 274, 19635, 'Lord Godfrey- Chapter 2 Intro'),
(36332, 0, 0, 'Tell me, Godfrey.  Those that stayed in Gilneas City so that we could live.  Were they following protocol?', 12, 0, 100, 0, 1, 19721, 'Greymane- Chapter 2 Intro'),
(36332, 0, 1, 'I didn''t think so.  Now hand me that potion, Krennan... and double the dosage.', 12, 0, 100, 0, 1, 19722, 'Greymane- Chapter 2 Intro');
