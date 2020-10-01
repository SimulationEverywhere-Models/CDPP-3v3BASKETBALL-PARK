[top]
components : basketballcourt@BasketballCourt
components : score@Score

in : totalRoundNumIn
out : scoreOut
out : totalScoreOut

Link : totalRoundNumIn totalRoundNumIn@basketballcourt
Link : scoreOut@basketballcourt scoreOut
Link : totalOut@basketballcourt totalScoreIn@score
Link : totalScoreOut@score totalScoreOut

[basketballcourt]
distribution : normal
mean : 24
deviation : 24

[score]

