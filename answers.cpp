#include "answers.h"
#include "sha.h"
#include "convert.h"
#include "aes.h"
#include <QDebug>

Answers::Answers() {
    answers = new QMap<QString, PieceShape>();
    answers->insert("R74Vaeh3pqeTzXQK7ZgzffHK7AMHuKjYOTR_RKgqlVw", PieceShape::ZShape);
    answers->insert("2YbP9jN6Zmf631KCB5N0BLeJ_HYps1MpJ64a1vbbrk0", PieceShape::ZShape);
    answers->insert("txvMtG89grzRfJzQ8m_yO38OLI6dCsGIw8UH8AFOeUs", PieceShape::ZShape);
    answers->insert("oVuA1VlLKQg7qZuzArVJw8V8QqkUaDIPMt4XbvJcRls", PieceShape::ZShape);
    answers->insert("ZGGrB79hbbc0_55SUKQeVVOWHz7Lee8Q5RU-tJkAa2Q", PieceShape::ZShape);
    answers->insert("kSwklPWrdx4r5gmQ7iRNkedAeAj_O-U8pmQkY3RSPQY", PieceShape::ZShape);
    answers->insert("JD0Xit3MA_EjUMdEHQV8gBplc7QafEVgX8Cy8G3b7A8", PieceShape::ZShape);
    answers->insert("_2HRTVwRY_hkVeh7KleQtKQma5Pyz1oHSfFQmSRQ9Jk", PieceShape::ZShape);
    answers->insert("r28oo-mQM3DGlL-ZRV34wE1vuO6IP1GLzjZ6CkGbAUY", PieceShape::ZShape);
    answers->insert("dVxDKX-Ne9ELqkbQPYMBwhIuEGXfkA5vhf_qrAPKyF0", PieceShape::ZShape);
    answers->insert("oXV7lKHpuyMh5j4op8aK8LXOWNdIYE4s3dNUAvxuj0M", PieceShape::ZShape);
    answers->insert("ZCBb-JGJ9x2iD33EMtb8Aevsj0Kor65Gj3ka9itzdik", PieceShape::ZShape);
    answers->insert("UlyL7iB3Nr-lejbtBBRzl-ZjrjNmjPRKibxGn1fZzZw", PieceShape::ZShape);
    answers->insert("Dn67gsWmE56zJKhqALN6QWV4RCWSsK5IalsS8k_XZqw", PieceShape::ZShape);
    answers->insert("kmuMcthmpDGBnGg3fRJZ37NGRh6413Bw5xCReJKI0Ag", PieceShape::ZShape);
    answers->insert("pArcAZgwigujwvPC_n8myWeH73caqxDXPC7zIboAX9s", PieceShape::ZShape);
    answers->insert("fpYC0lpEab4hgyzp1FMtOouhdbLapd_vKv_7I4fM4PI", PieceShape::ZShape);
    answers->insert("bog_9_HHY_G58BB4x-C9PtCKwuYjBD5SO61VoFGEHpA", PieceShape::ZShape);
    answers->insert("r4Er4hHgjpf7dUqNtCTT4lgFKWhy3YMa0OzdzRYGoiA", PieceShape::ZShape);
    answers->insert("myJ61EjXoomc7x7AcWQyP8e-PgjgyfCO5aww9sNqiMs", PieceShape::ZShape);

    answers->insert("01JxB8dKN_vpJFKh5YU7qto0s_xR5ibDpEjz_xysYCE", PieceShape::SShape);
    answers->insert("GzGnpMWGHQyuRID3ERa9EQm9nn9c5B4xHLFsxsunU_E", PieceShape::SShape);
    answers->insert("wSJXOu-SZX9SMIl6MmXj2_kdZ27jJesKJh533aWhBo8", PieceShape::SShape);
    answers->insert("kGDZ5rFXlVWDfgsnYfLqxqvBiUfmj3fbcc88e4Isl-U", PieceShape::SShape);
    answers->insert("xtE5BnVJmsG-0OPO5CN5F3-W3a79HyAVUeEIsHXL4p8", PieceShape::SShape);
    answers->insert("YeaiBjL80DfEHr0xDNVmW77AVdxbw5c84-rmQxk7Ad8", PieceShape::SShape);
    answers->insert("Xz93sbIx6OO510PgsOWAGuQ4j7T1BjiJzDPqPQ2RA7o", PieceShape::SShape);
    answers->insert("lUnawGyb0E-zxC3_xeRgRoDHEmeKmoasplQSF7CxTfQ", PieceShape::SShape);
    answers->insert("N1b_Gjwxj6OC0T8yc6PwtpnFoCwH9l8HErTWY9mZJNA", PieceShape::SShape);
    answers->insert("FI0DgG4nwywnvwkYKuqPeUCcsVgEZ6u8QOm-aTMCKGc", PieceShape::SShape);
    answers->insert("7WdS-d5FuEQyt6VJ3IhsnHOwaoHMrzvp5LCDuDacvvY", PieceShape::SShape);
    answers->insert("1DK86erw04_bo6qchkyg6X0nQd1wCzoM7kgkiiib-bQ", PieceShape::SShape);
    answers->insert("bqHp8TpdaMTwe7dkumhbtDZMUtvlym9D2oXgpfcK5os", PieceShape::SShape);
    answers->insert("rO47zaUlWAyUJVmOp9hIL3ug-V7-kL5G4nNJkVy3KRw", PieceShape::SShape);
    answers->insert("fL1zFBv318L7GyB6PfMf-Qpisi9T7kfTR_vv99DPg2Y", PieceShape::SShape);
    answers->insert("LujJMP9bicyvpMLiV5lR_LbZNaeaEaMPAyY9l3f5GTs", PieceShape::SShape);
    answers->insert("yJ2nyFCWiUyfhuZIam_wq15kzTkVRaS099OEhkM7GEg", PieceShape::SShape);
    answers->insert("cfnjOacwifBFLpw8DjDUnN7KGBupU_pAv1EI3k1GFeQ", PieceShape::SShape);
    answers->insert("yaR_wKKtnpiMyZdOOS7IvJccoHqvzOb4jIVVCo6csfY", PieceShape::SShape);
    answers->insert("4o0QW2SKCSWyg9BI76GftKQFf4YpObg0pRX-Gzd6xlY", PieceShape::SShape);

    answers->insert("Mn6aavVxz10H5mSb6pyu7hQIQH5Z2mAsujP_C3J1hUE", PieceShape::TShape);
    answers->insert("A_xjjyZI59INwgiTl6CHsmw5F91ZrHyu647Dbqh_R3k", PieceShape::TShape);
    answers->insert("i2IBPCytfRvEGGnI66PKbswmQ6evZ8Qun1RyLfsWCd8", PieceShape::TShape);
    answers->insert("3ulPvtUpvM2XqfvYsw_yeN1oXGnnWOxp5qA7s91cOHw", PieceShape::TShape);
    answers->insert("jMiAMON9hT6c7LzqynzVkkRwB2YEN0YvhDQGFeFFdKI", PieceShape::TShape);
    answers->insert("ERm-IhtQZ0zBLIoqY0LayX9AHvct3yU5D_dkSQ-o1yE", PieceShape::TShape);
    answers->insert("LkqqXxutxuMSn1HEzMb9HgbskDfelTASGEwfmrz1_dg", PieceShape::TShape);
    answers->insert("fI5ufIGzCUOqKFXmgmx_1SyAbmcIUQfxzJ_0JSNjpOY", PieceShape::TShape);
    answers->insert("qIZvV9BRhFZ4vkTEPtc-ZeLveJFqJe1Dbu_NlDTmS-4", PieceShape::TShape);
    answers->insert("Y7b0Uf8-dB6Ju0T1S5V9CpxILZqBqyQHK48OkIRfC8M", PieceShape::TShape);
    answers->insert("8A6SVbEKRnpV4PA7pQOiXAwQegjeTRr5gBBzRo-r8-0", PieceShape::TShape);
    answers->insert("P6BsyjEyNMo64kdOEjSgownSQyLffKARtRxqw0YLljE", PieceShape::TShape);
    answers->insert("1NajQg_Vhk3Cd6f6UBv74L3V1Y6LZXaNrAu7vkxSwt0", PieceShape::TShape);
    answers->insert("C2odUpN9HNyg7gOa6WyZRdNJbWZepE7UE0ZQj6k5Yr8", PieceShape::TShape);
    answers->insert("IHY2lwg3JvZzHEyjk1d12AHh-MGROpBWX_dxM61-ZBE", PieceShape::TShape);
    answers->insert("WtP-lb6Y4Y69xdyjBDEZ7lQFsRd3K9PSah6PzwMqYis", PieceShape::TShape);
    answers->insert("gaSJyTKvZan8-EXM_rQ18kj-PbRdEq5M0jOU-Bk2ECQ", PieceShape::TShape);
    answers->insert("rkaXVs2NQS1BQhFIlB8ul8TtxBmjsnP-RV_7IS5uj6Q", PieceShape::TShape);
    answers->insert("OJyXnbeu-q8x45vL3FUwnMGOF2ipGYQfw6OyU22kWXA", PieceShape::TShape);
    answers->insert("1HC6kvK8S8D1UjADae4y6N4j3nUs_udl3WhMUmdO8hY", PieceShape::TShape);

    answers->insert("ufOYSG4rcMsr8DEKHCrtfIDQbIu_rvu46CMe4TNvMqw", PieceShape::LShape);
    answers->insert("JV3uZyYAhtcbdm6fV9m_DE6kGYkiO-W5Rk_zSBH4Yvc", PieceShape::LShape);
    answers->insert("bLsrec-LUD_CSL4swLQKNlDUBtzS9B8V_GbmmlCYZBI", PieceShape::LShape);
    answers->insert("U-WFT1C68UtkFgkVFIHV9gihbtp4HdJ3gME1DhO0fww", PieceShape::LShape);
    answers->insert("iGNFfDKAuFBwoSX1VkMaZNRT-7mbCvma-dSpW7Ka5p8", PieceShape::LShape);
    answers->insert("NvZR2MJbnFlcqVVBVtBgYRDg7m02JXdc80-51jUMfRw", PieceShape::LShape);
    answers->insert("ayZOmUeW_l0rvosTHega_K-WYmd4YKjKPQ2m3aEyjzY", PieceShape::LShape);
    answers->insert("72KUZTyovhtejWN0fh3VhutAfbP9sC046wSnAyCIZ5c", PieceShape::LShape);
    answers->insert("Yw6CN8HSuNGDVfFjeMiiQbUpF25TXc7pxZqK7kOY1Dc", PieceShape::LShape);
    answers->insert("oz0BrA-shIraWGQhjuTeAWid9FRFN0_xkbGe7QU-g70", PieceShape::LShape);
    answers->insert("MYPIYqNE31tpsLVpur5y0ilVrM_sg5qMjOHQ3AEStp0", PieceShape::LShape);
    answers->insert("9v2G-fq6rOneoKqfvodWhKpYn4LNSofNVcx_QFtN5As", PieceShape::LShape);
    answers->insert("OiMr7jDriHtgTb6YjA55BGeHBcqbLiJICpet-qAgaq0", PieceShape::LShape);
    answers->insert("eNCEK4SAPDxu_f95XRI8xjf0qw-hucZ6wPRNm5v_0Lc", PieceShape::LShape);
    answers->insert("G7g6aJ4Iud0ANbmfdAMmUxNksBnsAAbqW1av5qizKdM", PieceShape::LShape);
    answers->insert("MlHEQZXcKTrBoIp8vPyHDiGDoYhya1vROQ39VUy6M08", PieceShape::LShape);
    answers->insert("8DwhVIlSusao_pPP_Ik2hvF-1rYyFcwMNkxZCGwHi90", PieceShape::LShape);
    answers->insert("XA8husEpzCWvI5unRNP1PTSCQfLySFAwCud-VBWnd4I", PieceShape::LShape);
    answers->insert("fTgfS5f-A8OAPDw0mTIEzdBqsstCVgtQGFxZ3fluqLs", PieceShape::LShape);
    answers->insert("6PRlPkYTi7GeuTHkLuDRk-x3tI51Gdo-ONJi3PmjPOo", PieceShape::LShape);

    answers->insert("SC9JvgtRazsrSYkE7320Nr50lH_fXcglyHlk01B2Z-k", PieceShape::JShape);
    answers->insert("8ZQHly_fOC58-Yr83wFwbP9bH-tcMOy0JvWuCEloUeY", PieceShape::JShape);
    answers->insert("b_chxokyAhkzQC7uwkndXYXLvjfCNkfAnWAGeQawJA4", PieceShape::JShape);
    answers->insert("Xv8K8puw--Mja8mtJV7PFaUD8RVhfxTcA-3faFd9uM0", PieceShape::JShape);
    answers->insert("PyAJxtNHRgbUj7Xu8gt30AMr6Hd0TCuMDmKAqHaXSz4", PieceShape::JShape);
    answers->insert("i2Wo4PzybmS-56BaQXEzJLNZvWldeXu3ijKoDi_QXZQ", PieceShape::JShape);
    answers->insert("2KR1Fhl5pI-SRLm9v-WcMjZQid9QN5Kt4A-pmO-sleM", PieceShape::JShape);
    answers->insert("AlAH95heq5iP-nms3Wv3B9dKCQ9C8aEyVTsP2cre-mU", PieceShape::JShape);
    answers->insert("Tw39Cwa0OmVDF824yKCs19khS5TY38VVm7mIpdhoEcA", PieceShape::JShape);
    answers->insert("qEDVC4seQ_7GopAS4Re6bhd2aeYc9Q4lYjgY5Rs3l4c", PieceShape::JShape);
    answers->insert("aidkmxpDilecWuttBW4mLcjYkAX9ANnNbnReTFxrZ0I", PieceShape::JShape);
    answers->insert("q71Jf2o9NGVo1SieyeeyesyyoxyMLunXPClO_-XB0tw", PieceShape::JShape);
    answers->insert("XwogfUnYyS0QCbTo8KxXmSc9HVjTJ2DwghdMYczr2g8", PieceShape::JShape);
    answers->insert("UokHki9IN3rpU2PO1SFRuUl6UNWYnGWpTX9U9llXk2I", PieceShape::JShape);
    answers->insert("Ib7OQ8oCL5aM4LQqpMZFiMiDvOv07T__y571IH3piyI", PieceShape::JShape);
    answers->insert("-R3Md2shs-BF4i1rTJy48oExo1F8u3qpJxguqxjQ0Bs", PieceShape::JShape);
    answers->insert("b7qYfOD30dOTk34rFyYp_PNlCU14HztBNJ2_lTNXBnU", PieceShape::JShape);
    answers->insert("81O2WhRMG9MiE59UgY0egeePKgPn2jbi-w04CFjmfiE", PieceShape::JShape);
    answers->insert("lFV_B2bE3sx7B-vUucE02UsDBJEjZJKnd-_uTlzzElo", PieceShape::JShape);
    answers->insert("skbNJYf5A404etT_pWs5dzgNibm_AUG_8BccsHUlfJI", PieceShape::JShape);

    answers->insert("i-lWTpdmMDUfBE28G2UDE1GLXj-iWT12omFFgMzFHqY", PieceShape::SquareShape);
    answers->insert("TGvTp85XcdIR2J5_9PtOkGmq_mzeMnPf7ts7i0b1fzk", PieceShape::SquareShape);
    answers->insert("WOtg61jdVT19W-p3yZ5MWT9HotIifR6IYFSJg_USEGw", PieceShape::SquareShape);
    answers->insert("my3jnSLoJRzCx4-MeoXbZpmSthaB5I78VZaL4EFMSMo", PieceShape::SquareShape);
    answers->insert("eF93Klx9ApIgM1A2npuKc7FMbSxyl2CkaOGZphgTgIo", PieceShape::SquareShape);
    answers->insert("w67H1xzmb8AkG7bQMlqaCMytoaaMZVyzaPOGwiWevNs", PieceShape::SquareShape);
    answers->insert("70i64_6G2Tmgq4wZ21jJwSScTacwASeN6EjbQN2nGFg", PieceShape::SquareShape);
    answers->insert("neha4_jm04IJEJvEG5xr6-tsWyDIgQjEsPD8lL1zWY0", PieceShape::SquareShape);
    answers->insert("ysw_32Q9Gyz8gTotq10AE4ET8xsIxxwf6bg4uXiTiFg", PieceShape::SquareShape);
    answers->insert("MzSFvKtkuH0YFEfE1xP-b9OvoYqOprVpvyqTqZVswgk", PieceShape::SquareShape);
    answers->insert("L-7wjtF6VC4k7U93_3HXFFEN6obAThCJ2rRrcPwJ_vg", PieceShape::SquareShape);
    answers->insert("hO_tl3BXzBxVlu9B8nHPta3sTfYm4HRlouts8sNde_Q", PieceShape::SquareShape);
    answers->insert("OAYCtJYQqOGfYhtw4CWGIsVZe0shxxQoSciF9ggjPi4", PieceShape::SquareShape);
    answers->insert("psOeigz_BGNjnZDkpr1lh8XYEkKqMfu_mLteeikjz-g", PieceShape::SquareShape);
    answers->insert("IHej-ZmPCdAqGQ-jREui5RsZUwG3ZTIA0o1OSlsmTSM", PieceShape::SquareShape);
    answers->insert("Ry05dlgPC7oZUJlNAHwtWUVhsrpGACccNdeiopowP-k", PieceShape::SquareShape);
    answers->insert("R4XVIwsotpwCTLIKYwOB0hO-iFjh8CEKpWLiCWPRzVk", PieceShape::SquareShape);
    answers->insert("T4YuPlII1ILhigkZ-pvu4L8kRvM2VBtCJEzyhGFYEFI", PieceShape::SquareShape);
    answers->insert("bo5zFh3qnFPQdhc8E9dbOi2enndZw6A1dx8nr6lLQGQ", PieceShape::SquareShape);
    answers->insert("wudInVy9lf7otjxaMQVnCY35jQ0gWQX2hy9MmAywP_E", PieceShape::SquareShape);

    answers->insert("-AcuDQS7hJK2ZEH6o7YIB7Y29yWcmCzr6YRDRXs-Gjw", PieceShape::LineShape);
    answers->insert("QgvysoMzbunoXiNiUfrNzFqiKVP9ZMfe3ycyvVIMg8Y", PieceShape::LineShape);
    answers->insert("g0J5VTzlxg5QaZ74ZHLyI-T8dzA9_6w0SlE2ZlavZNM", PieceShape::LineShape);
    answers->insert("yb39jCAzcJy47jF6pNiee_czIGGWcbm7R_yBAi--CCE", PieceShape::LineShape);
    answers->insert("dE85hqghZMuMevLymOH0f1MtjoftPJUe5lPg-EUSjPQ", PieceShape::LineShape);
    answers->insert("VtnKO6kZHtBfWRT5lvo5UlX2fOUqPCPJrAB62V3JRLU", PieceShape::LineShape);
    answers->insert("3_051mPAhuirpFvNcBLuOHrB7F-KCRyZA1DIxXYQkso", PieceShape::LineShape);
    answers->insert("L4rfiLqnu1S1Oi7oHQH1hYBMLeMl6zna1SN59q2QyPk", PieceShape::LineShape);
    answers->insert("g7708Cp0ln6lNcZj48IdyDl_agguMA5n-gPT0uBnr-0", PieceShape::LineShape);
    answers->insert("kJ-OqenFaaynh8Y-Bbpry0BW_j3_9ac8Lenr9RToGtM", PieceShape::LineShape);
    answers->insert("GY7u75XAf2bLqUekp_kYefB6sYrAacYwa5kss6UpZ8g", PieceShape::LineShape);
    answers->insert("oBPnA-3mSz3hyrJWB7W02uBbm7KjZXQAH6wihMIM150", PieceShape::LineShape);
    answers->insert("txFUNKEOu5jltltdWqp-3ZClHr_M-1Foc0ZlFypIGz0", PieceShape::LineShape);
    answers->insert("hvATqQ2eOEYADHjysSmKYdb4dO21_HlUyz8ScrPWqmA", PieceShape::LineShape);
    answers->insert("HbWnPWzhlfsA46YbkOuAoDLSFsFBD8czirx_8-zG5Wk", PieceShape::LineShape);
    answers->insert("yyzeoPXvF41pfw5HmVllgWGJSR111kPcgm3uFbV18Gw", PieceShape::LineShape);
    answers->insert("Sf8zx-Bcxg7I_8ehsIlXKbtuzxvJA6vrfIlc61jg5mM", PieceShape::LineShape);
    answers->insert("TVpGJgtkK4jc2dpV6M3VSF4x44Flbqjo-atKHjwqGOU", PieceShape::LineShape);
    answers->insert("qzwusdq6OIrKXk-4t0shbhlCyxeeS-dIhedctLyRBNc", PieceShape::LineShape);
    answers->insert("FFGTNQk4zAJvK4MLeQgb2B9f4Dn6hz9RR66oR4Z7osE", PieceShape::LineShape);
	
	    /*QList<qint32> list = QList<qint32>();
    list.append(422901);
    list.append(903157);
    list.append(544249);
    list.append(741363);
    list.append(999200);
    list.append(691542);
    list.append(552698);
    list.append(703844);
    list.append(213938);
    list.append(361382);
    list.append(321501);
    list.append(248480);
    list.append(496641);
    list.append(546882);
    list.append(738816);
    list.append(779942);
    list.append(962937);
    list.append(367304);
    list.append(154698);
    list.append(763213);
    list.append(447202);
    list.append(540066);
    list.append(798432);
    list.append(811284);
    list.append(372707);
    list.append(443510);
    list.append(569651);
    list.append(623846);
    list.append(435441);
    list.append(249634);
    list.append(637447);
    list.append(889022);
    list.append(920159);
    list.append(406628);
    list.append(815424);
    list.append(203032);
    list.append(598342);
    list.append(208975);
    list.append(836568);
    list.append(965514);
    list.append(353206);
    list.append(215393);
    list.append(947521);
    list.append(506791);
    list.append(545732);
    list.append(936935);
    list.append(894529);
    list.append(123034);
    list.append(970507);
    list.append(584954);
    list.append(729314);
    list.append(838113);
    list.append(245463);
    list.append(677265);
    list.append(123125);
    list.append(321022);
    list.append(538191);
    list.append(839727);
    list.append(314587);
    list.append(351095);
    list.append(906058);
    list.append(423589);
    list.append(972761);
    list.append(110167);
    list.append(374231);
    list.append(160160);
    list.append(618017);
    list.append(238093);
    list.append(500028);
    list.append(387441);
    list.append(281495);
    list.append(574946);
    list.append(112668);
    list.append(913576);
    list.append(257009);
    list.append(856091);
    list.append(824371);
    list.append(592516);
    list.append(304254);
    list.append(435391);
    list.append(802102);
    list.append(291859);
    list.append(471476);
    list.append(898562);
    list.append(817229);
    list.append(201895);
    list.append(233294);
    list.append(123422);
    list.append(651855);
    list.append(149967);
    list.append(385574);
    list.append(897092);
    list.append(826521);
    list.append(747710);
    list.append(921641);
    list.append(636851);
    list.append(725930);
    list.append(884019);
    list.append(771117);
    list.append(889581);
    list.append(368654);
    list.append(243384);
    list.append(348601);
    list.append(423128);
    list.append(453827);
    list.append(464680);
    list.append(841105);
    list.append(824065);
    list.append(320833);
    list.append(474521);
    list.append(519068);
    list.append(770430);
    list.append(691221);
    list.append(311982);
    list.append(651208);
    list.append(714177);
    list.append(971003);
    list.append(194679);
    list.append(270622);
    list.append(738015);
    list.append(403081);
    list.append(187123);
    list.append(715168);
    list.append(256249);
    list.append(967119);
    list.append(668294);
    list.append(340707);
    list.append(965033);
    list.append(685817);
    list.append(414204);
    list.append(464037);
    list.append(255529);
    list.append(638465);
    list.append(985210);
    list.append(402909);
    list.append(548997);
    list.append(465290);
    list.append(799749);
    list.append(279756);
    list.append(994313);
    for (qint32 i: list){
        QString hash = calculateHash(calculateHash(QString::number(i) + salt()) + calculateHash(salt() + salt()) + salt());
        qDebug() << hash;
    }*/

   //qDebug() << "Enc salt = " <<  Convert::bytes2Base64UrlSafe(AES::encrypt(QByteArray::fromHex(QString("72bcb39523f5ceb5bf0d798401815daed8061191030a7d1c3365c2dca986915ef4e417650f8fda1126bb74696ecb085c133320b9ac45571708251cb2b1fef0f5956b43d7cf042dd9196a848e4a9cf760078926ca1cb6ea152c5fab3447a25508fc51c7840aa18e29bfe9c49ed7cf2ff80f2780").toUtf8())));
	
}

Answers::~Answers() {
    answers->clear();
    delete answers;
}

bool Answers::isCorrect(QString answer) {
    auto hash = calculateHash(calculateHash(answer + salt()) + calculateHash(salt() + salt()) + salt());
    return answers->contains(hash);
}

PieceShape Answers::getShape(QString answer){
    auto hash = calculateHash(calculateHash(answer + salt()) + calculateHash(salt() + salt()) + salt());
    return answers->value(hash);
}

QString Answers::calculateHash(QString data) {
    return Convert::bytes2Base64UrlSafe(SHA::sha3(QString(data).toUtf8()));
}

QString Answers::salt() {
    auto encSalt = QString(ENC_SALT);
    auto dec = AES::decrypt(Convert::base64UrlSafe2Bytes(encSalt));
    return calculateHash(Convert::bytes2Base64UrlSafe(dec));
}

