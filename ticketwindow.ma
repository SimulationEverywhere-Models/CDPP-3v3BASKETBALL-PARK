[top]
components : ticketwindow@TicketWindow


out : moneyOut
out : audienceOut
in : audienceIn
in : workerIn

Link : audienceIn audienceIn@ticketwindow
Link : workerIn workerIn@ticketwindow
Link : audienceOut@ticketwindow audienceOut
Link : moneyOut@ticketwindow moneyOut

[ticketwindow]


