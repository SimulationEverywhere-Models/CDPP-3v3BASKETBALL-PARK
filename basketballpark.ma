[top]
components : audience@Audience
components : ticketwindow@TicketWindow
components : Court

out : audienceOut moneyOut out totalScoreOut
in : totalRoundNumIn audienceIn workerIn

Link : totalRoundNumIn totalRoundNumIn@Court
Link : scoreOut@Court in@audience
Link : out@audience out
Link : totalScoreOut@Court totalScoreOut
Link : audienceIn audienceIn@ticketwindow
Link : workerIn workerIn@ticketwindow
Link : audienceOut@ticketwindow audienceIn@audience
Link : audienceOut@audience audienceOut
Link : moneyOut@ticketwindow moneyOut

[ticketwindow]


[Court]
components : basketballcourt@BasketballCourt
components : score@Score

in : totalRoundNumIn
out : scoreOut totalScoreOut

Link : totalRoundNumIn totalRoundNumIn@basketballcourt
Link : scoreOut@basketballcourt scoreOut
Link : totalOut@basketballcourt totalScoreIn@score
Link : totalScoreOut@score totalScoreOut


[basketballcourt]
distribution : normal
mean : 24
deviation : 24

[score]

[audience]
 


