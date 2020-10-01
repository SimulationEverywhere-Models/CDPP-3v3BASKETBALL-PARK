[top]
components : basketballcourt@BasketballCourt


out : scoreOut
out : totalOut
in : totalRoundNumIn

Link : totalRoundNumIn totalRoundNumIn@basketballcourt
Link : scoreOut@basketballcourt scoreOut
Link : totalOut@basketballcourt totalOut

[basketballcourt]
distribution : normal
mean : 24
deviation : 24
