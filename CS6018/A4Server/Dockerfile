# B# Build the Ktor application inside a Linux container
   FROM eclipse-temurin:21-jdk AS build

   WORKDIR /app

   COPY . .

   # Strip Windows line endings from gradlew, then make it executable
   RUN sed -i 's/\r$//' gradlew && chmod +x gradlew
   RUN ./gradlew installDist --no-daemon

   # Run only the packaged application
   FROM eclipse-temurin:21-jre

   WORKDIR /app

   COPY --from=build /app/build/install/ktor-server-6018/ ./

   ENV PHOTO_DIR=/data/photos
   EXPOSE 8080

   ENTRYPOINT ["./bin/ktor-server-6018"]