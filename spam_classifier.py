# Import necessary libraries
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.model_selection import train_test_split
from sklearn import metrics

# Example data (messages and labels)
messages = [
    "Win a cash prize now!", "Free offer just for you", 
    "Meeting at 5 pm", "Let's catch up tomorrow", 
    "Claim your free prize", "How about lunch tomorrow?"
]
labels = ['spam', 'spam', 'not_spam', 'not_spam', 'spam', 'not_spam']

# Split data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(messages, labels, test_size=0.33)

# Convert text data into feature vectors (word counts)
vectorizer = CountVectorizer()
X_train = vectorizer.fit_transform(X_train)
X_test = vectorizer.transform(X_test)

# Train the Naive Bayes model
model = MultinomialNB()
model.fit(X_train, y_train)

# Function to predict whether a new message is spam or not
def predict_spam(message):
    message_vector = vectorizer.transform([message])
    prediction = model.predict(message_vector)
    return prediction[0]

# Input text to predict
user_input = input("Enter a message: ")

# Predict and display result
result = predict_spam(user_input)
print(f"The message is classified as: {result}")
