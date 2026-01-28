
#set document(author: "Cesar H Ornelas-Rascon", 
              title: [Graphics Plots],
              
              )
              
#let unary(num,..) =if calc.rem(num,2)< 1 {}else{num} 


#set page(paper: "a4",
          columns: 2,
          numbering: "1.",
          header: align(center,"AOT CONFIDENTIAL"))

#set text(
  font: "Libertinus Serif",
  size: 11pt,
)

#show title: set text(size: 17pt)
#show title: set align(center)



#set heading(numbering: "1.")

#place(
  top + center,
  float: true,
  scope: "parent",
  clearance: 2em,
)[
#title()
#align(center)[
    Cesar H. Ornelas-Rascon
  ]


#outline()
]

= Introduction
#lorem(300)

= Related Work
#lorem(200)

= Functions
#lorem(200)
= Who
#lorem(200)
= Well
#lorem(200)
= Resource
• Color palette article: https://iquilezles.org/articles/palettes/
• Color palette webapp: http://dev.thi.ng/gradients/
• Graphtoy: https://graphtoy.com/

